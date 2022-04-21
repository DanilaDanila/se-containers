#ifndef TEMPLATES_LIST_2022_02_03
#define TEMPLATES_LIST_2022_02_03

namespace lab618 {
template <class T> class CSingleLinkedList {
private:
  struct leaf {
    T data;
    leaf *pnext;
    leaf(T &data, leaf *pnext) : data(data), pnext(pnext) {}
  };

public:
  class CIterator {
  public:
    CIterator() : m_pBegin(nullptr), m_pCurrent(nullptr) {}

    CIterator(leaf *p) : m_pBegin(nullptr), m_pCurrent(p) {}

    CIterator(const CIterator &src)
        : m_pBegin(src.m_pBegin), m_pCurrent(src.m_pCurrent) {}

    ~CIterator() {}

    CIterator &operator=(const CIterator &src) {
      m_pCurrent = src.m_pCurrent;
      m_pBegin = src.m_pBegin;
      return *this;
    }

    bool operator!=(const CIterator &it) const {
      return m_pCurrent != it.m_pCurrent || m_pBegin != m_pBegin;
    }

    void operator++() {
      m_pCurrent = (m_pCurrent != nullptr) ? m_pCurrent->pnext : m_pBegin;
      m_pBegin = nullptr;
    }

    T &getData() { return m_pCurrent->data; }

    T &operator*() { return m_pCurrent->data; }

    leaf *getLeaf() { return m_pCurrent; }

    void setLeaf(leaf *p) { m_pCurrent = p; }

    void setLeafPreBegin(leaf *p) {
      m_pBegin = p;
      m_pCurrent = nullptr;
    }

    bool isValid() { return m_pCurrent != nullptr || m_pBegin != nullptr; }

  private:
    //храним голову списка, если мы находимся перед началом
    leaf *m_pBegin;
    // храним текущее положение
    leaf *m_pCurrent;
  };

public:
  CSingleLinkedList() : m_pBegin(nullptr), m_pEnd(nullptr) {}

  virtual ~CSingleLinkedList() { clear(); }

  void pushBack(T &data) {
    leaf *new_leaf = new leaf(data, nullptr);

    if (m_pBegin == nullptr) {
      m_pBegin = m_pEnd = new_leaf;
    } else {
      m_pEnd = m_pEnd->pnext = new_leaf;
    }
  }

  void pushFront(T &data) {
    leaf *new_leaf = new leaf(data, m_pBegin);

    if (m_pBegin == nullptr) {
      m_pBegin = m_pEnd = new_leaf;
    } else {
      m_pBegin = new_leaf;
    }
  }

  T popFront() {
    T data = m_pBegin->data;

    leaf *tmp = m_pBegin;
    m_pBegin = m_pBegin->pnext;
    delete tmp;

    if (m_pBegin == nullptr)
      m_pEnd = nullptr;

    return data;
  }

  // изменяет состояние итератора. выставляет предыдущую позицию.
  void erase(CIterator &it) {
    leaf *tmp = it.getLeaf();

    if (tmp == m_pBegin) {
      it.setLeafPreBegin(tmp->pnext);
      m_pBegin = tmp->pnext;
    } else {
      if (tmp == m_pEnd) {
        for (m_pEnd = m_pBegin; m_pEnd->pnext->pnext != nullptr;
             m_pEnd = m_pEnd->pnext)
          ;
      }
      leaf *prev = m_pBegin;
      for (; prev->pnext != tmp; prev = prev->pnext)
        ;

      prev->pnext = tmp->pnext;
      it.setLeaf(prev);
    }

    delete tmp;
  }

  int getSize() {
    int len = 0;

    for (leaf *it = m_pBegin; it != nullptr; it = it->pnext)
      ++len;

    return len;
  }

  void clear() {
    while (m_pBegin != nullptr) {
      leaf *tmp = m_pBegin;
      m_pBegin = m_pBegin->pnext;

      delete tmp;
    }

    m_pBegin = nullptr;
    m_pEnd = nullptr;
  }

  CIterator begin() const { return CIterator(m_pBegin); }

private:
  leaf *m_pBegin, *m_pEnd;
};

// ***************************************************************************

template <class T> class CDualLinkedList {
private:
  struct leaf {
    T data;
    leaf *pnext, *pprev;
    leaf(T &data, leaf *pprev, leaf *pnext)
        : data(data), pnext(pnext), pprev(pprev) {}
  };

public:
  class CIterator {
  public:
    CIterator() : m_pBegin(nullptr), m_pCurrent(nullptr), m_pEnd(nullptr) {}

    CIterator(leaf *p) : m_pBegin(nullptr), m_pCurrent(p), m_pEnd(nullptr) {}

    CIterator(const CIterator &src)
        : m_pBegin(src.m_pBegin), m_pCurrent(src.m_pCurrent),
          m_pEnd(src.m_pEnd) {}

    ~CIterator() {}

    CIterator &operator=(const CIterator &src) {
      m_pCurrent = src.m_pCurrent;
      m_pBegin = src.m_pBegin;
      m_pEnd = src.m_pEnd;
      return *this;
    }

    bool operator!=(const CIterator &it) const {
      return m_pCurrent != it.m_pCurrent || m_pBegin != it.m_pBegin ||
             m_pEnd != it.m_pEnd;
    }

    void operator++() {
      if (m_pCurrent != nullptr) {
        m_pCurrent = m_pCurrent->pnext;
      } else if (m_pBegin != nullptr) {
        m_pCurrent = m_pBegin;
        m_pBegin = nullptr;
      } else {
        m_pCurrent = nullptr;
        m_pEnd = nullptr;
      }
    }

    void operator--() {
      if (m_pCurrent != nullptr) {
        m_pCurrent = m_pCurrent->pprev;
      } else if (m_pEnd != nullptr) {
        m_pCurrent = m_pEnd;
        m_pEnd = nullptr;
      } else {
        m_pCurrent = nullptr;
        m_pBegin = nullptr;
      }
    }

    T &getData() { return m_pCurrent->data; }

    T &operator*() { return m_pCurrent->data; }

    leaf *getLeaf() { return m_pCurrent; }

    // применяется в erase и eraseAndNext
    void setLeaf(leaf *p) { m_pCurrent = p; }

    // применяется в erase и eraseAndNext
    void setLeafPreBegin(leaf *p) {
      m_pBegin = p;
      m_pCurrent = nullptr;
      m_pEnd = nullptr;
    }

    // применяется в erase и eraseAndNext
    void setLeafPostEnd(leaf *p) {
      m_pEnd = p;
      m_pCurrent = nullptr;
      m_pBegin = nullptr;
    }

    bool isValid() {
      return m_pCurrent != nullptr || m_pBegin != nullptr || m_pEnd != nullptr;
    }

  private:
    //храним голову списка, если мы находимся перед началом
    leaf *m_pBegin;
    // храним текущее положение
    leaf *m_pCurrent;
    //храним конец списка, если мы находимся после конца
    leaf *m_pEnd;
  };

public:
  CDualLinkedList() : m_pBegin(nullptr), m_pEnd(nullptr) {}

  virtual ~CDualLinkedList() { clear(); }

  void pushBack(T &data) {
    leaf *new_leaf = new leaf(data, m_pEnd, nullptr);

    if (m_pBegin == nullptr) {
      m_pBegin = m_pEnd = new_leaf;
    } else {
      m_pEnd = m_pEnd->pnext = new_leaf;
    }
  }

  T popBack() {
    T data = m_pEnd->data;

    leaf *tmp = m_pEnd;
    m_pEnd = m_pEnd->pprev;
    m_pEnd->pnext = nullptr;
    delete tmp;

    if (m_pEnd == nullptr)
      m_pBegin = nullptr;

    return data;
  }

  void pushFront(T &data) {
    leaf *new_leaf = new leaf(data, nullptr, m_pBegin);

    if (m_pBegin == nullptr) {
      m_pBegin = m_pEnd = new_leaf;
    } else {
      m_pBegin = m_pBegin->pprev = new_leaf;
    }
  }

  T popFront() {
    T data = m_pBegin->data;

    leaf *tmp = m_pBegin;

    if (m_pBegin->pnext == nullptr) {
      m_pBegin = m_pEnd = nullptr;
    } else {
      m_pBegin = m_pBegin->pnext;
      m_pBegin->pprev = nullptr;
    }

    delete tmp;

    return data;
  }

  // изменяет состояние итератора. выставляет предыдущую позицию.
  void erase(CIterator &it) {
    leaf *tmp = it.getLeaf();

    if (tmp == m_pBegin) {
      it.setLeafPreBegin(tmp->pnext);
      m_pBegin = tmp->pnext;
      m_pBegin->pprev = nullptr;
    } else {
      it.setLeaf(tmp->pprev);
      tmp->pprev->pnext = tmp->pnext;
      if (tmp != m_pEnd) {
        tmp->pnext->pprev = tmp->pprev;
      } else {
        m_pEnd = tmp->pprev;
      }
    }

    delete tmp;
  }

  // изменяет состояние итератора. выставляет следующую позицию.
  void eraseAndNext(CIterator &it) {
    leaf *tmp = it.getLeaf();

    if (tmp == m_pEnd) {
      it.setLeafPostEnd(tmp->pprev);
      m_pEnd = tmp->pprev;
      m_pEnd->pnext = nullptr;
    } else {
      it.setLeaf(tmp->pnext);
      tmp->pnext->pprev = tmp->pprev;
      if (tmp != m_pBegin) {
        tmp->pprev->pnext = tmp->pnext;
      } else {
        m_pBegin = tmp->pnext;
      }
    }

    delete tmp;
  }

  int getSize() {
    int len = 0;

    for (leaf *it = m_pBegin; it != nullptr; it = it->pnext)
      ++len;

    return len;
  }

  void clear() {
    while (m_pBegin != nullptr) {
      leaf *tmp = m_pBegin;
      m_pBegin = m_pBegin->pnext;

      delete tmp;
    }

    m_pBegin = m_pEnd = nullptr;
  }

  CIterator begin() const { return CIterator(m_pBegin); }

  CIterator end() const { return CIterator(m_pEnd); }

private:
  leaf *m_pBegin, *m_pEnd;
};
}; // namespace lab618

#endif //#ifndef TEMPLATES_LIST_2022_02_03
