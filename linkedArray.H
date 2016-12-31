#ifndef _LINKEDARRAY_H
#define _LINKEDARRAY_H

#include<stdlib.h>

template<class Type> class LinkedArray;
template<class Type>
class LinkedArrayItem
 {friend class LinkedArray<Type>;
 public:
    LinkedArrayItem();
    LinkedArrayItem(const LinkedArrayItem<Type>&);
    static int Compare(const void*, const void*);
    void AddPrior(LinkedArrayItem<Type>* const itemAddr);
    void AddNext(LinkedArrayItem<Type>* const itemAddr);
    void Remove();

    Type item;
    LinkedArrayItem<Type>* priorItem,
                         * nextItem;
    int index;
 };

template<class Type>
class LinkedArray
 {public:
    LinkedArray(const int numAvailable);
    LinkedArray(const int numAvailable, const Type* const, const int );
    ~LinkedArray();
    LinkedArray<Type>& Reset();
    LinkedArray<Type>& Reset(const Type* const, const int);
    LinkedArray<Type>& SetInitialLink();
    LinkedArray<Type>& SetListLinks();
    LinkedArray<Type>& SetCurrentAtHead();
    LinkedArray<Type>& SetCurrentAtTail();
    LinkedArray<Type>& SetCurrentAtItem(const int);
    LinkedArray<Type>& SetCurrentAtHole();
    LinkedArray<Type>& Prior();
    LinkedArray<Type>& Next();
    LinkedArray<Type>& AddPrior();
    LinkedArray<Type>& AddNext();
    LinkedArray<Type>& SetMoveSource();
    LinkedArray<Type>& MovePrior();
    LinkedArray<Type>& MoveNext();
    LinkedArray<Type>& RemoveAndSetPrior();
    LinkedArray<Type>& RemoveAndSetNext();
    LinkedArray<Type>& Sort();
    int GetItemIndex() const;
    Type& GetData() const;
    Type& operator[](const int);
    int GetNumItems() const;
    int GetNumAvailableItems() const;


   LinkedArray(const LinkedArray<Type>&);
   LinkedArray<Type>& operator=(const LinkedArray<Type>&);
   void SetFromArray(const Type* const, const int);
   LinkedArray<Type>& RemoveAndSetItem(LinkedArrayItem<Type>* const);

   int numAvailableItems,
       numItems,
       numHoles,
       numLinks;
   LinkedArrayItem<Type>* items,
                        * headItem,
                        * tailItem,
                        * currentItem,
                        * moveSource,
                        ** freeHoles,
                        ** initialLinks;
 };

template<class Type>
inline
LinkedArrayItem<Type>::LinkedArrayItem() {}

template<class Type>
inline int
LinkedArrayItem<Type>::Compare(const void* addr1, const void* addr2)
 {return (*(LinkedArrayItem<Type>**)addr1)->item<
         (*(LinkedArrayItem<Type>**)addr2)->item ? -1 :
         (*(LinkedArrayItem<Type>**)addr1)->item!=
         (*(LinkedArrayItem<Type>**)addr2)->item;
 }

template<class Type>
inline void
LinkedArrayItem<Type>::AddPrior(LinkedArrayItem<Type>* const itemAddr)
 {itemAddr->priorItem=priorItem;
  itemAddr->nextItem=this;
  priorItem->nextItem=itemAddr;
  priorItem=itemAddr;
 }

template<class Type>
inline void
LinkedArrayItem<Type>::AddNext(LinkedArrayItem<Type>* const itemAddr)
 {itemAddr->priorItem=this;
  itemAddr->nextItem=nextItem;
  nextItem->priorItem=itemAddr;
  nextItem=itemAddr;
 }

template<class Type>
inline void
LinkedArrayItem<Type>::Remove()
 {priorItem->nextItem=nextItem;
  nextItem->priorItem=priorItem;
  priorItem=nextItem=NULL;
 }

template<class Type>
inline LinkedArray<Type>::
LinkedArray(const int numAvailItems):numAvailableItems(numAvailItems),
                                     numItems(0),
                                     numHoles(numAvailItems),
                                     numLinks(0),
                                     headItem(NULL),
                                     tailItem(NULL),
                                     currentItem(NULL),
                                     moveSource(NULL)
 {items=new LinkedArrayItem<Type>[numAvailableItems];
  freeHoles=new LinkedArrayItem<Type>*[numAvailableItems];
  initialLinks=new LinkedArrayItem<Type>*[numAvailableItems];
  for (int i=0; i<numHoles; ++i)
   {items[i].priorItem=items[i].nextItem=NULL;
    items[i].index=i;
    freeHoles[numHoles-i-1]=&items[i];
   }
 }

template<class Type>
inline LinkedArray<Type>::
LinkedArray(const int numAvailItems,
             const Type* const itemArray, const int numItemArray):
                                   numAvailableItems(numAvailItems),
                                   numItems(numAvailItems>numItemArray ? numItemArray
                                                                       : numAvailItems),
                                   numHoles(numAvailItems-numItems),
                                   numLinks(numItems),
                                   headItem(items),
                                   tailItem(&items[numItems-1]),
                                   currentItem(headItem),
                                   moveSource(NULL)
 {items=new LinkedArrayItem<Type>[numAvailableItems];
  freeHoles=new LinkedArrayItem<Type>*[numAvailableItems];
  initialLinks=new LinkedArrayItem<Type>*[numAvailableItems];
  SetFromArray(itemArray, numItemArray);
 }

template<class Type>
inline LinkedArray<Type>::
~LinkedArray()
 {
   delete [] initialLinks;
   delete [] freeHoles;
   delete [] items;
 }

template<class Type>
inline LinkedArray<Type>&
LinkedArray<Type>::Reset()
 {numItems=numLinks=0;
  numHoles=numAvailableItems;
  headItem=tailItem=currentItem=moveSource=NULL;
  for (int i=0; i<numHoles; ++i)
   {items[i].priorItem=items[i].nextItem=NULL;
    items[i].index=i;
    freeHoles[numHoles-i-1]=&items[i];
   }
  return *this;
 }

template<class Type>
inline LinkedArray<Type>&
LinkedArray<Type>::Reset(const Type* const itemArray, const int numItemArray)
 {numItems=numLinks=numAvailableItems>numItemArray ? numItemArray
                                                   : numAvailableItems;
  numHoles=numAvailableItems-numItems;
  headItem=currentItem=items;
  tailItem=&items[numItems-1];
  moveSource=NULL;
  SetFromArray(itemArray, numItemArray);
  return *this;
 }

template<class Type>
inline void
LinkedArray<Type>::SetFromArray(const Type* const itemArray, const int numItemArray)
 {for (int i=0; i<numItems; ++i)
   {items[i].item=itemArray[i];
    items[i].priorItem=i ? &items[i-1]
                         : tailItem;
    items[i].nextItem=i<numItems-1 ? &items[i+1]
                                   : headItem;
    items[i].index=i;
    initialLinks[i]=&items[i];
   }
  for (int i=numItems; i<numAvailableItems; ++i)
   {items[i].priorItem=items[i].nextItem=NULL;
    items[i].index=i;
    freeHoles[numAvailableItems-i-1]=&items[i];
   }
 }

template<class Type>
inline LinkedArray<Type>&
LinkedArray<Type>::SetInitialLink()
 {initialLinks[numLinks++]=currentItem;
  return *this;
 }

template<class Type>
inline LinkedArray<Type>&
LinkedArray<Type>::SetListLinks()
 {if (numLinks)
   {numItems=numLinks;
    numHoles=numAvailableItems-numItems;
    headItem=currentItem=initialLinks[0];
    tailItem=initialLinks[numLinks-1];
    for (int i=0; i<numItems; ++i)
     {initialLinks[i]->priorItem=i ? initialLinks[i-1]
                                   : tailItem;
      initialLinks[i]->nextItem=i<numItems-1 ? initialLinks[i+1]
                                             : headItem;
     }
    for (int i=numItems; i<numAvailableItems; ++i)
      freeHoles[numAvailableItems-i-1]=&items[i];
    numLinks=0;
   }
  return *this;
 }

template<class Type>
inline LinkedArray<Type>&
LinkedArray<Type>::SetCurrentAtHead()
 {currentItem=headItem;
  return *this;
 }

template<class Type>
inline LinkedArray<Type>&
LinkedArray<Type>::SetCurrentAtTail()
 {currentItem=tailItem;
  return *this;
 }

template<class Type>
inline LinkedArray<Type>&
LinkedArray<Type>::SetCurrentAtItem(const int index)
 {currentItem=&items[index];
  return *this;
 }

template<class Type>
inline LinkedArray<Type>&
LinkedArray<Type>::SetCurrentAtHole()
 {currentItem=freeHoles[numHoles-1];
  return *this;
 }

template<class Type>
inline LinkedArray<Type>&
LinkedArray<Type>::Prior()
 {if (currentItem)
    currentItem=currentItem->priorItem;
  return *this;
 }

template<class Type>
inline LinkedArray<Type>&
LinkedArray<Type>::Next()
 {if (currentItem)
    currentItem=currentItem->nextItem;
  return *this;
 }

template<class Type>
inline LinkedArray<Type>&
LinkedArray<Type>::AddPrior()
 {--numHoles;
  if (numItems++)
   {currentItem->AddPrior(freeHoles[numHoles]);
    if (headItem==currentItem) headItem=freeHoles[numHoles];
   }
  else
   {currentItem=freeHoles[numHoles];
    headItem=tailItem=currentItem->priorItem=currentItem->nextItem=currentItem;
   }
  return *this;
 }

template<class Type>
inline LinkedArray<Type>&
LinkedArray<Type>::AddNext()
 {--numHoles;
  if (numItems++)
   {currentItem->AddNext(freeHoles[numHoles]);
    if (tailItem==currentItem) tailItem=freeHoles[numHoles];
   }
  else
   {currentItem=freeHoles[numHoles];
    headItem=tailItem=currentItem->priorItem=currentItem->nextItem=currentItem;
   }
  return *this;
 }

template<class Type>
inline LinkedArray<Type>&
LinkedArray<Type>::SetMoveSource()
 {moveSource=currentItem;
  return *this;
 }

template<class Type>
inline LinkedArray<Type>&
LinkedArray<Type>::MovePrior()
 {if (moveSource!=currentItem)
   {if (headItem==moveSource) headItem=moveSource->nextItem;
    if (tailItem==moveSource) tailItem=moveSource->priorItem;
    moveSource->Remove();
    currentItem->AddPrior(moveSource);
    if (headItem==currentItem) headItem=moveSource;
   }
  return *this;
 }

template<class Type>
inline LinkedArray<Type>&
LinkedArray<Type>::MoveNext()
 {if (moveSource!=currentItem)
   {if (headItem==moveSource) headItem=moveSource->nextItem;
    if (tailItem==moveSource) tailItem=moveSource->priorItem;
    moveSource->Remove();
    currentItem->AddNext(moveSource);
    if (tailItem==currentItem) tailItem=moveSource;
   }
  return *this;
 }

template<class Type>
inline LinkedArray<Type>&
LinkedArray<Type>::RemoveAndSetPrior()
 {return RemoveAndSetItem(currentItem->priorItem);
 }

template<class Type>
inline LinkedArray<Type>&
LinkedArray<Type>::RemoveAndSetNext()
 {return RemoveAndSetItem(currentItem->nextItem);
 }

template<class Type>
inline LinkedArray<Type>&
LinkedArray<Type>::RemoveAndSetItem(LinkedArrayItem<Type>* const
                                                 itemAddr)
 {if (itemAddr)
  {freeHoles[numHoles++]=currentItem;
   if (--numItems)
    {if (headItem==currentItem) headItem=currentItem->nextItem;
     if (tailItem==currentItem) tailItem=currentItem->priorItem;
     currentItem->Remove();
     currentItem=itemAddr;
    }
   else
    {currentItem->Remove();
     headItem=tailItem=currentItem=NULL;
    }
  }
 else
   currentItem=NULL;
  return *this;
 }

template<class Type>
inline LinkedArray<Type>&
LinkedArray<Type>::Sort()
 {qsort(initialLinks, numLinks, sizeof(LinkedArrayItem<Type>*),
        LinkedArrayItem<Type>::Compare);
  return *this;
 }

template<class Type>
inline int
LinkedArray<Type>::GetItemIndex() const
 {return currentItem->index;
 }

template<class Type>
inline Type&
LinkedArray<Type>::GetData() const
 {
         return currentItem->item;
 }

template<class Type>
inline Type&
LinkedArray<Type>::operator[](const int index)
 {currentItem=&items[index];
  return items[index].item;
 }

template<class Type>
inline int
LinkedArray<Type>::GetNumItems() const
 {return numItems;
 }

template<class Type>
inline int
LinkedArray<Type>::GetNumAvailableItems() const
 {return numAvailableItems;
 }

#endif
