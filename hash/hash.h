#ifndef HASH_HEAD_H_2021_03_11
#define HASH_HEAD_H_2021_03_11

#include "mm.h" // необходимо использовать свой memorymanager

#include <iostream>

namespace lab618 {
/*
 * Шаблонный класс CHash.
 * В качестве параметров шаблона применяется:
 * тип - T;
 * функция вычисления хеша - unsigned int HashFunc(const T* pElement);
 * функция сравнения - int Compare(const T *pElement, const T* pElement2).
 *
 *  Класс реализует алгоритм контейнера Хеш-таблица (ассоциативный массив).
 * Данный алгоритм базируется на идее формирования линейной адресации
 * произвольных элементов в зависимости от специально вычисляемого целого
 * значения, уникального для каждого элемента (хеш). Формирование линейной
 * адресации позволяет получать и сохранять элементы в контейнер за время не
 * зависящее от числа элементов в контейнере — O(1). В идеальном случае каждому
 * хешу соответствует ячейка в линейном массиве данных. На самом деле подобрать
 * функцию вычисления хеша, таким образом, чтобы соблюдалась уникальность
 * сложно, или получаются числа очень большой размерности. Для преодоления
 * данной проблемы, в Хеш-таблице допускаются коллизии — одинаковые значения,
 * уникальность элементов определяется их полями (функциями сравнения).
 * Существует два способа разрешения коллизий — разреженная Хеш-таблица и
 * Хеш-таблица со списками. Разреженные Хеш-таблицы при возникновении коллизии
 * начинают искать первую свободную ячейку в самой таблице, поиск аналогично
 * происходит от ячейки с номером равным значению хеша, пока не найдется нужный
 * элемент. Хеш-таблица со списками, в каждой ячейке Хеш-таблицы хранит начало
 * списка элементов с одинаковыми значениями хеша. Соответственно, вставка
 * производится по алгоритму: вычисляем значение хеша для элемента, проверяем
 * есть ли в списке с данным индексом (значение хеш функции) данный элемент с
 * помощью функции сравнения, если нет до добавляем его в список. Поиск
 * производится по алгоритму: вычисляем значение хеша для элемента, проверяем
 * есть ли в списке с данным индексом искомый элемент с помощью функции
 * сравнения. Размер Хеш-таблицы, как правило, меньше размерности функции
 * вычисления хеша, поэтому вычисленное значение хеша ограничивают по размеру
 * таблицы с помощью операции вычисления остатка от деления. Функция вычисления
 * хеша и операция сравнения задаются как параметры шаблона, что позволяет
 * построить разные Хеш-таблицы для одного набора элементов. Основные недостатки
 * Хеш-таблиц:
 *   1. Сложность подбора хорошей хеш функции (функции дающей наименьшее число
 * коллизий);
 *   2. Отсутствие упорядоченности элементов;
 *   3. Вычислительная сложность хеш функции может добавить большую константу в
 * вычислительную сложность алгоритма.
 *
 * Данный класс реализует алгоритм Хеш-таблицы со списками
 * Данный класс не хранит данные — хранит, только указатели на них.
 * Хранение данных производится вне рамок данного класса!
 */
template <class T, unsigned int (*HashFunc)(const T *pElement),
          int (*Compare)(const T *pElement, const T *pElement2)>
class CHash {
private:
  /*
   * Лист списка элементов. Обратите внимание, что хранится указатель на данные.
   * Данный класс не хранит данные — хранит, только указатели на них.
   * Хранение данных производится вне рамок данного класса!
   */
  struct leaf {
    T *pData;
    leaf *pnext;
  };

public:
  /*
   * Исключение, которое применяется при нехватке памяти на работу алгоритма
   */
  class CMemoryException {
  public:
    CMemoryException() {}
  };

public:
  /*
   * Конструктор с параметрами: размер Хеш-таблицы, и размер блока памяти для
   * менеджера памяти. Размер Хеш таблицы реализуем жестко — изменение размера
   * таблицы в зависимости от числа элементов в контейнере не требуется. Все
   * создаваемые листики списков разрешения коллизий храним в менеджере памяти.
   */
  CHash(int hashTableSize, int defaultBlockSize)
      : m_tableSize(hashTableSize), m_pTable(nullptr),
        m_Memory(defaultBlockSize, true) {}

  /*
   * Деструктор. Должен освобождать всю выделенную память
   */
  virtual ~CHash() { clear(); }

  /*
   * Функция добавления элемента в Хеш-таблицу. Возвращает false, если элемент
   * уже есть и true, если элемент добавлен.
   */
  bool add(T *pElement) {
    if (m_pTable == nullptr) {
      m_pTable = new leaf *[m_tableSize];
      for (int i = 0; i < m_tableSize; ++i) {
        m_pTable[i] = nullptr;
      }
    }

    unsigned idx;
    leaf *ptr = findLeaf(pElement, idx);

    if (ptr == nullptr) {
      if (m_pTable[idx] == nullptr) {
        leaf *tmp = m_Memory.newObject();
        m_pTable[idx] = new (tmp) leaf;
        m_pTable[idx]->pnext = nullptr;

        m_pTable[idx]->pData = pElement;
      } else {
        leaf *it;
        for (it = m_pTable[idx]; it->pnext != nullptr; it = it->pnext)
          ;

        leaf *tmp = m_Memory.newObject();
        tmp = new (tmp) leaf;
        tmp->pData = pElement;
        tmp->pnext = nullptr;

        it->pnext = tmp;
      }

      return true;
    } else {
      return false;
    }
  }

  /*
   * Функция обновления элемента в Хеш-таблице. Обновляет, если элемент уже есть
   * добавляет, если элемента еще нет. Возвращает false, если был добавлен новый
   * элемент, true если элемент обновлен.
   */
  bool update(T *pElement) {
    unsigned idx;
    leaf *ptr = findLeaf(pElement, idx);

    if (ptr == nullptr) {
      this->add(pElement);
      return false;
    } else {
      ptr->pData = pElement;
      return true;
    }
  }

  /*
   * Функция поиска элемента в Хеш-таблице. Возвращает указатель на данные. Если
   * элемента не нашлось, то null. Обратите внимание, что для поиска
   * используется частично заполненный объект, т.е. В нем должны быть заполнены
   * поля на основе которых рассчитывается хеш.
   */
  T *find(const T &element) {
    unsigned idx;
    leaf *ptr = findLeaf(&element, idx);
    return (ptr != nullptr) ? ptr->pData : nullptr;
  }

  /*
   *Функция удаления элемента из Хеш-таблицы. Возвращает false, если не нашлось
   *элемента, true если элемент был удален.
   */
  bool remove(const T &element) {
    unsigned idx;
    leaf *ptr = findLeaf(&element, idx);

    if (ptr != nullptr) {
      leaf *elem;
      for (elem = m_pTable[idx]; elem != nullptr; elem = elem->pnext) {
        if (Compare(&element, elem->pData) == 0) {
          if (elem == m_pTable[idx]) {
            m_pTable[idx] = elem->pnext;
          } else {
            leaf *prev;
            for (prev = m_pTable[idx]; prev->pnext != elem; prev = prev->pnext)
              ;

            prev->pnext = elem->pnext;
          }

          m_Memory.deleteObject(elem);
          return true;
        }
      }

      return false;
    } else {
      return false;
    }
  }

  /*
   * Удаление всех элементов. Можно вызвать в деструкторе
   */
  void clear() {
    if (m_pTable == nullptr) {
      return;
    }

    delete[] m_pTable;
    m_pTable = nullptr;
    // Остальное очистит m_Memory
    m_Memory.clear();
  }

private:
  /*
   * Элементарная функция поиска узла в Хеш-таблицу. Возвращает найденный узел и
   * в переменную idx выставляет актуальный индекс хеш-таблицы. Данную функцию
   * следует использовать в функциях add, update, find. Алгоритм функции:
   *  1. вычисляем хеш функцию
   *  2. вычисляем индекс в Хеш-таблице (приводим вычисленное значение хеш
   * функции к размеру массива)
   *  3. Перебираем список значений и если нашли, то возвращаем его.
   *  4. Если ничего не нашли, то возвращаем null
   */
  leaf *findLeaf(const T *pElement, unsigned int &idx) {
    unsigned hash = HashFunc(pElement);
    idx = hash % m_tableSize;

    leaf *ptr;
    for (ptr = m_pTable[idx]; ptr != nullptr; ptr = ptr->pnext) {
      if (Compare(pElement, ptr->pData) == 0) {
        break;
      }
    }

    return ptr;
  }

  int m_tableSize; // Размер Хеш-таблицы

  leaf **m_pTable; // Хеш-таблица

  // Менеджер памяти, предназначен для хранение листов списков разрешения
  // коллизий
  CMemoryManager<leaf> m_Memory;
};
}; // namespace lab618

#endif // #define HASH_HEAD_H_2021_03_11
