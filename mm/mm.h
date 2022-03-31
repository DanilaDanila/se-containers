#ifndef MEMORY_MANAGER_HEAD_H_2022_02_17
#define MEMORY_MANAGER_HEAD_H_2022_02_17

namespace lab618 {
template <class T> class CMemoryManager {
private:
  struct block {
    // Массив данных блока
    T *pdata;
    // Адрес следующего блока
    block *pnext;
    // Первая свободная ячейка
    int firstFreeIndex;
    // Число заполненных ячеек
    int usedCount;
  };

public:
  class CException {
  public:
    CException() {}
  };

public:
  CMemoryManager(int _default_block_size,
                 bool isDeleteElementsOnDestruct = false)
      : m_blkSize(_default_block_size),

        m_pBlocks(nullptr), m_pCurrentBlk(nullptr),
        m_isDeleteElementsOnDestruct(isDeleteElementsOnDestruct) {}

  virtual ~CMemoryManager() { clear(); }

  // Получить адрес нового элемента из менеджера
  T *newObject() {
    if (!m_pBlocks) {
      m_pBlocks = m_pCurrentBlk = newBlock();
    }

    T *object;

    if (m_pCurrentBlk->firstFreeIndex != -1) {
      object = &m_pCurrentBlk->pdata[m_pCurrentBlk->firstFreeIndex];
      m_pCurrentBlk->firstFreeIndex = *reinterpret_cast<int *>(object);
    } else {
      block *free_block;
      for (free_block = m_pBlocks; free_block != nullptr;
           free_block = free_block->pnext) {
        if (free_block->firstFreeIndex != -1) {
          break;
        }
      }

      if (free_block == nullptr) {
        free_block = newBlock();
        m_pCurrentBlk->pnext = free_block;
        m_pCurrentBlk = free_block;
      }

      object = &free_block->pdata[free_block->firstFreeIndex];
      free_block->firstFreeIndex = *reinterpret_cast<int *>(object);
    }

    return object;
  }

  // Освободить элемент в менеджере
  bool deleteObject(T *p) {
    block *holder = m_pBlocks;
    while ((p - holder->pdata) > m_blkSize) {
      holder = holder->pnext;

      if (holder == nullptr) {
        return false;
      }
    }

    *reinterpret_cast<int *>(p) = holder->firstFreeIndex;
    holder->firstFreeIndex = (p - holder->pdata);

    return true;
  }

  // Очистка данных, зависит от m_isDeleteElementsOnDestruct
  void clear() {
    if (m_isDeleteElementsOnDestruct) {
      for (auto it = m_pBlocks; it != nullptr;) {
        auto tmp = it;
        it = it->pnext;
        deleteBlock(tmp);
      }
    }
  }

private:
  // Создать новый блок данных. применяется в newObject
  block *newBlock() {
    block *new_block = new block;
    new_block->pdata = new T[m_blkSize];
    new_block->pnext = nullptr;
    new_block->firstFreeIndex = 0;
    new_block->usedCount = 0;

    for (int i = 0; i < m_blkSize - 1; ++i)
      *reinterpret_cast<int *>(&new_block->pdata[i]) = i + 1;
    *reinterpret_cast<int *>(&new_block->pdata[m_blkSize - 1]) = -1;

    m_pCurrentBlk = new_block;
    return new_block;
  }

  // Освободить память блока данных. Применяется в clear
  void deleteBlock(block *p) {
    delete[] p->pdata;
    delete p;
  }

  // Размер блока
  int m_blkSize;
  // Начало списка блоков
  block *m_pBlocks;
  // Текущий блок
  block *m_pCurrentBlk;
  // Удалять ли элементы при освобождении
  bool m_isDeleteElementsOnDestruct;
};
}; // namespace lab618

#endif // #define MEMORY_MANAGER_HEAD_H_2022_02_17
