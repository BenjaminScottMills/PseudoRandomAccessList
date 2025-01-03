#include <math.h>

// A node in a PRAL. Methods are public so that they may be called by the Pral. Not intended for direct use.
template <typename T>
struct PralNode
{
    T value;
    PralNode<T> * next = NULL;
    PralNode<T> * prev = NULL;
    PralNode<T> * jumpAdress = NULL;
    
    PralNode(T inValue, PralNode<T> * inPrev = NULL, PralNode<T> * inNext = NULL)
    {
        value = inValue;
        prev = inPrev;
        next = inNext;
    }

    // For use in Pral creation. Creates the binary tree of jump nodes with height jumpDepth for a Pral representing the section of input starting at index beforeSpace with a
    // size of size. myIndex is the intended index of this PralNode in the Pral. addressArr will have its contents altered (starting at arrIndex) so that the left-side nodes in
    // each pair in the created tree are contained within in sequential order. indexArr will also be altered to contain the intended indecies (in the Pral) of the nodes in 
    // adressArr at the corresponding indecies.
    void createTree(std::initializer_list<T> const & input, unsigned int size, unsigned int beforeSpace, short jumpDepth, int indexArr[], PralNode<T> * adressArr[], short * arrIndex, int myIndex)
    {
        if(jumpDepth <= 0)
        {
            if(next)
            {
                indexArr[*arrIndex] = myIndex;
                adressArr[*arrIndex] = this;

                *arrIndex += 1;
            }
            return;
        }

        jumpAdress = new PralNode<T>(*(input.begin() + size/2 + beforeSpace));
        jumpAdress->prev = new PralNode<T>(*(input.begin() + size/2 + beforeSpace - 1), NULL, jumpAdress);

        jumpAdress->prev->createTree(input, size / 2, beforeSpace, jumpDepth - 1, indexArr, adressArr, arrIndex, size/2 + beforeSpace - 1);
        jumpAdress->createTree(input, (1 + size) / 2, beforeSpace + size/2, jumpDepth - 1, indexArr, adressArr, arrIndex, size/2 + beforeSpace);

        if(next)
        {
            indexArr[*arrIndex] = myIndex;
            adressArr[*arrIndex] = this;

            *arrIndex += 1;
        }
    }

    // For use in Pral creation. Creates the binary tree of jump nodes with height jumpDepth for a Pral representing the section of input starting at index beforeSpace with a
    // size of size. myIndex is the intended index of this PralNode in the Pral. addressArr will have its contents altered (starting at arrIndex) so that the left-side nodes in
    // each pair in the created tree are contained within in sequential order. indexArr will also be altered to contain the intended indecies (in the Pral) of the nodes in 
    // adressArr at the corresponding indecies.
    void createTree(T input[], unsigned int size, unsigned int beforeSpace, short jumpDepth, int indexArr[], PralNode<T> * adressArr[], short * arrIndex, int myIndex)
    {
        if(jumpDepth <= 0)
        {
            if(next)
            {
                indexArr[*arrIndex] = myIndex;
                adressArr[*arrIndex] = this;

                *arrIndex += 1;
            }
            return;
        }

        jumpAdress = new PralNode<T>(input[size/2 + beforeSpace]);
        jumpAdress->prev = new PralNode<T>(input[size/2 + beforeSpace - 1], NULL, jumpAdress);

        jumpAdress->prev->createTree(input, size / 2, beforeSpace, jumpDepth - 1, indexArr, adressArr, arrIndex, size/2 + beforeSpace - 1);
        jumpAdress->createTree(input, (1 + size) / 2, beforeSpace + size/2, jumpDepth - 1, indexArr, adressArr, arrIndex, size/2 + beforeSpace);

        if(next)
        {
            indexArr[*arrIndex] = myIndex;
            adressArr[*arrIndex] = this;

            *arrIndex += 1;
        }
    }

    // For use in Pral creation. Creates the binary tree of jump nodes with height jumpDepth for a Pral representing input with a size of size. myIndex is the intended index
    // of this PralNode in the Pral. If input is the root of a subtree in a larger Pral, then beforeSpace is the number of elements that appear ahead of the section covered
    // by the subtree. addressArr will have its contents altered (starting at arrIndex) so that the left-side nodes in each pair in the created tree are contained within in
    // sequential order. indexArr will also be altered to contain the intended indecies (in the Pral) of the nodes in adressArr at the corresponding indecies. 
    void createTree(PralNode<T> * input, unsigned int size, unsigned int beforeSpace, short jumpDepth, int indexArr[], PralNode<T> * adressArr[], short * arrIndex, int myIndex)
    {
        if(jumpDepth <= 0)
        {
            if(next)
            {
                indexArr[*arrIndex] = myIndex;
                adressArr[*arrIndex] = this;

                *arrIndex += 1;
            }
            return;
        }

        jumpAdress = new PralNode<T>(input->jumpAdress->value);
        jumpAdress->prev = new PralNode<T>(input->jumpAdress->prev->value, NULL, jumpAdress);
        
        jumpAdress->prev->createTree(input->jumpAdress->prev, size / 2, beforeSpace, jumpDepth - 1, indexArr, adressArr, arrIndex, size/2 + beforeSpace - 1);
        jumpAdress->createTree(input->jumpAdress, (1 + size) / 2, beforeSpace + size/2, jumpDepth - 1, indexArr, adressArr, arrIndex, size/2 + beforeSpace);

        if(next)
        {
            indexArr[*arrIndex] = myIndex;
            adressArr[*arrIndex] = this;

            *arrIndex += 1;
        }
    }

    // Adds another layer to the binary tree of jump nodes. sizeOfPral is the size of the segment covered by this and the adjacent node in the tree. remainingJumpDepth is the
    // intented new depth of the tree after a new layer is added. isAimingForward is true if this is a right-side node in a pair, false if this is a left-side node.
    void addJumpPointLayer(unsigned int sizeOfPral, short remainingJumpDepth, bool isAimingForward)
    {
        if(remainingJumpDepth <= 0) return;

        unsigned int jumpPointIndex;
        unsigned int effSize;
        PralNode<T> * iterationAdress = NULL;

        if(isAimingForward)
        {
            effSize = (1 + sizeOfPral) / 2;
            
            if(remainingJumpDepth == 1)
            {
                jumpPointIndex = effSize/2;
                iterationAdress = next;

                for(unsigned int i = 1; i < jumpPointIndex; i++)
                {
                    iterationAdress = iterationAdress->next;
                }

                jumpAdress = iterationAdress;
            }
            else
            {
                jumpAdress->addJumpPointLayer(effSize, remainingJumpDepth-1, true);
            }

            if(prev != NULL) prev->addJumpPointLayer(sizeOfPral, remainingJumpDepth, false);
        }
        else
        {
            effSize = sizeOfPral / 2;

            if(remainingJumpDepth == 1)
            {
                jumpPointIndex = effSize/2;
                iterationAdress = prev;

                for(unsigned int i = effSize - 2; i > jumpPointIndex; i--)
                {
                    iterationAdress = iterationAdress->prev;
                }

                jumpAdress = iterationAdress;
            }
            else
            {
                jumpAdress->addJumpPointLayer(effSize, remainingJumpDepth-1, true);
            }
        }
    }

    // Removes the bottom layer from the tree of jump nodes. remainingJumpDepth is the intended depth after the bottom layer has been removed.
    void removeJumpPointLayer(short remainingJumpDepth)
    {
        if(remainingJumpDepth == 0)
        {
            jumpAdress = NULL;

            if(prev) prev->jumpAdress = NULL;
        }
        else
        {
            jumpAdress->removeJumpPointLayer(remainingJumpDepth - 1);

            if(prev) prev->jumpAdress->removeJumpPointLayer(remainingJumpDepth - 1);
        }
    }

    // Produces the adress of the node at index targetIndex in the section of a Pral (with size size) covered by the jump-tree rooted at this. walkDistance is the maximum
    // distance a node may be from the jump tree. isAimingForward is true if this is a right-side node in a pair, false if this is a left-side node.
    PralNode<T> * jumpToNode(unsigned int targetIndex, unsigned int size, short walkDistance, bool isAimingForward)
    {
        PralNode<T> * returnNode;

        if(isAimingForward)
        {
            if(walkDistance >= targetIndex)
            {
                returnNode = this;

                for(unsigned int i = 0; i < targetIndex; i++)
                {
                    returnNode = returnNode->next;
                }

                return returnNode;
            }
        }
        else if(size - 1 - walkDistance <= targetIndex)
        {
            returnNode = this;

            for(unsigned int i = size - 1; i > targetIndex; i--)
            {
                returnNode = returnNode->prev;
            }

            return returnNode;
        }

        if(targetIndex >= size/2)
        {
            return jumpAdress->jumpToNode(targetIndex - (size/2), (1 + size) / 2, walkDistance, true);
        }

        return jumpAdress->prev->jumpToNode(targetIndex, size / 2, walkDistance, false);
    }

    // Produces the adress of the parent node in the jump tree of the node at targetIndex in the section of a Pral (with size size) covered by the jump-tree rooted at this.
    // walkDistance is the maximum distance a node may be from the jump tree. if the node at targetIndex is not in the jump tree, produces NULL.
    PralNode<T> * searchTreeForParent(unsigned int targetIndex, unsigned int size, short walkDistance)
    {
        if(walkDistance >= targetIndex || targetIndex >= size - 1 - walkDistance || !jumpAdress) return NULL;

        if(targetIndex >= size/2)
        {
            if(targetIndex == size/2) return this;
            
            return jumpAdress->searchTreeForParent(targetIndex - (size/2), (1 + size) / 2, walkDistance);
        }

        return jumpAdress->prev->searchTreeForParent(targetIndex, size / 2, walkDistance);
    }

    // Methods for tree shifting after insertion and erasure:

    // Shifts all descendants (excluding this) in the jump tree right by 1 node in the Pral. jumpDepth is the remaining height of the jump tree.
    void shiftAllRightByOne(short jumpDepth)
    {
        if(jumpDepth == 0) return;
        jumpDepth --;

        jumpAdress->next->jumpAdress = jumpAdress->jumpAdress;
        jumpAdress->jumpAdress = jumpAdress->prev->jumpAdress;
        jumpAdress->prev->jumpAdress = NULL;

        jumpAdress = jumpAdress->next;

        jumpAdress->shiftAllRightByOne(jumpDepth);
        jumpAdress->prev->shiftAllRightByOne(jumpDepth);
    }

    // Shifts all descendants (excluding this) in the jump tree left by 1 node in the Pral. jumpDepth is the remaining height of the jump tree.
    void shiftAllLeftByOne(short jumpDepth)
    {
        if(jumpDepth == 0) return;
        jumpDepth --;

        jumpAdress->prev->prev->jumpAdress = jumpAdress->prev->jumpAdress;
        jumpAdress->prev->jumpAdress = jumpAdress->jumpAdress;
        jumpAdress->jumpAdress = NULL;

        jumpAdress = jumpAdress->prev;

        jumpAdress->shiftAllLeftByOne(jumpDepth);
        jumpAdress->prev->shiftAllLeftByOne(jumpDepth);
    }

    // Called to shift the jump nodes after an element has been inserted into the Pral, the Sub-Pral (the section of the Pral covered by the jump tree rooted at this) is NOT set
    // to increase in size by 1, and NO Sub-Pral fully to the left of the one rooted at this is set to increase in size. insertionIndex is the index that the new element was
    // inserted at within the Sub-Pral, size is the number of elements in the Sub-Pral (before the insertion), and jumpDepth is the remaining height in the jump tree.
    void insertionJumpPointShiftNoSegmentSizeIncrease(unsigned int insertionIndex, unsigned int size, short jumpDepth)
    {
        if(jumpDepth == 0) return;
        jumpDepth --;

        if(insertionIndex > size/2)
        {
            if(insertionIndex < size) jumpAdress->insertionJumpPointShiftNoSegmentSizeIncrease(insertionIndex - (size/2), (size + 1) / 2, jumpDepth);
        }
        else
        {
            jumpAdress->prev->prev->jumpAdress = jumpAdress->prev->jumpAdress;
            jumpAdress->prev->jumpAdress = jumpAdress->jumpAdress;
            jumpAdress->jumpAdress = NULL;

            jumpAdress = jumpAdress->prev;

            jumpAdress->shiftAllLeftByOne(jumpDepth);
            jumpAdress->prev->insertionJumpPointShiftNoSegmentSizeIncrease(insertionIndex, size/2, jumpDepth);
        }
    }

    // Called to shift the jump nodes after an element has been inserted into the Pral, the Sub-Pral (the section of the Pral covered by the jump tree rooted at this) is NOT set
    // to increase in size by 1, and a Sub-Pral fully to the left of the one rooted at this IS set to increase in size. insertionIndex is the index that the new element was
    // inserted at within the Sub-Pral, size is the number of elements in the Sub-Pral (before the insertion), and jumpDepth is the remaining height in the jump tree.
    void rightShiftedInsertionJumpPointShiftNoSegmentSizeIncrease(unsigned int insertionIndex, unsigned int size, short jumpDepth)
    {
        if(jumpDepth == 0) return;
        jumpDepth --;

        if(insertionIndex > size/2)
        {
            jumpAdress->next->jumpAdress = jumpAdress->jumpAdress;
            jumpAdress->jumpAdress = jumpAdress->prev->jumpAdress;
            jumpAdress->prev->jumpAdress = NULL;

            jumpAdress = jumpAdress->next;
            
            if(insertionIndex < size) jumpAdress->rightShiftedInsertionJumpPointShiftNoSegmentSizeIncrease(insertionIndex - (size/2), (size + 1) / 2, jumpDepth);
            else jumpAdress->shiftAllRightByOne(jumpDepth);

            jumpAdress->prev->shiftAllRightByOne(jumpDepth);
        }
        else
        {
            jumpAdress->prev->rightShiftedInsertionJumpPointShiftNoSegmentSizeIncrease(insertionIndex, size/2, jumpDepth);
        }
    }

    // Called to shift the jump nodes after an element has been inserted into the Pral, and the Sub-Pral (the section of the Pral covered by the jump tree rooted at this) is set
    // to increase in size by 1. insertionIndex is the index that the new element was inserted at within the Sub-Pral, size is the number of elements in the Sub-Pral (before the
    // insertion), and jumpDepth is the remaining height in the jump tree.
    void insertionJumpPointShift(unsigned int insertionIndex, unsigned int size, short jumpDepth)
    {
        if(jumpDepth == 0) return;
        jumpDepth --;
        
        if(insertionIndex > size/2)// the position of the index is not affecting anything here.
        {
            if(size % 2)// size % 2 == 1.
            {
                jumpAdress->next->jumpAdress = jumpAdress->jumpAdress;
                jumpAdress->jumpAdress = jumpAdress->prev->jumpAdress;
                jumpAdress->prev->jumpAdress = NULL;

                jumpAdress = jumpAdress->next;

                if(insertionIndex < size) jumpAdress->rightShiftedInsertionJumpPointShiftNoSegmentSizeIncrease(insertionIndex - (size/2), (size + 1) / 2, jumpDepth);
                else jumpAdress->shiftAllRightByOne(jumpDepth);

                jumpAdress->prev->insertionJumpPointShift(insertionIndex, size/2, jumpDepth);
            }
            else// size % 2 == 0.
            {
                jumpAdress->insertionJumpPointShift(insertionIndex - (size/2), (size + 1) / 2, jumpDepth);
            }
        }
        else// insertionIndex <= size/2. Left shift required.
        {
            if(size % 2)// size % 2 == 1.
            {
                jumpAdress->prev->insertionJumpPointShift(insertionIndex, size/2, jumpDepth);
            }
            else// size % 2 == 0.
            {
                jumpAdress->prev->prev->jumpAdress = jumpAdress->prev->jumpAdress;
                jumpAdress->prev->jumpAdress = jumpAdress->jumpAdress;
                jumpAdress->jumpAdress = NULL;

                jumpAdress = jumpAdress->prev;
                
                jumpAdress->insertionJumpPointShift(0, (size + 1) / 2, jumpDepth);

                jumpAdress->prev->insertionJumpPointShiftNoSegmentSizeIncrease(insertionIndex, size/2, jumpDepth);
            }
        }
    }

    // Called to shift the jump nodes after an element has been erased from the Pral, the Sub-Pral (the section of the Pral covered by the jump tree rooted at this) is NOT set
    // to decrease in size by 1, and NO Sub-Pral to the left of the one rooted at this is set to decrease in size. erasureIndex is the index of the erased element within the
    // Sub-Pral, size is the number of elements in the Sub-Pral (before the erasure), and jumpDepth is the remaining height in the jump tree.
    void erasureJumpPointShiftNoSegmentSizeDecrease(unsigned int erasureIndex, unsigned int size, short jumpDepth)
    {
        if(jumpDepth == 0) return;
        jumpDepth --;

        if(erasureIndex >= size/2)
        {
            if(erasureIndex < size) jumpAdress->erasureJumpPointShiftNoSegmentSizeDecrease(erasureIndex - (size/2), (size + 1) / 2, jumpDepth);
        }
        else
        {
            jumpAdress->next->jumpAdress = jumpAdress->jumpAdress;
            jumpAdress->jumpAdress = jumpAdress->prev->jumpAdress;
            jumpAdress->prev->jumpAdress = NULL;

            jumpAdress = jumpAdress->next;

            jumpAdress->shiftAllRightByOne(jumpDepth);
            jumpAdress->prev->erasureJumpPointShiftNoSegmentSizeDecrease(erasureIndex, size/2, jumpDepth);
        }
    }

    // Called to shift the jump nodes after an element has been erased from the Pral, the Sub-Pral (the section of the Pral covered by the jump tree rooted at this) is NOT set
    // to decrease in size by 1, and a Sub-Pral to the left of the one rooted at this IS set to decrease in size. erasureIndex is the index of the erased element within the
    // Sub-Pral, size is the number of elements in the Sub-Pral (before the erasure), and jumpDepth is the remaining height in the jump tree.
    void leftShiftedErasureJumpPointShiftNoSegmentSizeDecrease(unsigned int erasureIndex, unsigned int size, short jumpDepth)
    {
        if(jumpDepth == 0) return;
        jumpDepth --;

        if(erasureIndex >= size/2)
        {
            jumpAdress->prev->prev->jumpAdress = jumpAdress->prev->jumpAdress;
            jumpAdress->prev->jumpAdress = jumpAdress->jumpAdress;
            jumpAdress->jumpAdress = NULL;

            jumpAdress = jumpAdress->prev;

            if(erasureIndex < size) jumpAdress->leftShiftedErasureJumpPointShiftNoSegmentSizeDecrease(erasureIndex - (size/2), (size + 1) / 2, jumpDepth);
            else jumpAdress->shiftAllLeftByOne(jumpDepth);

            jumpAdress->prev->shiftAllLeftByOne(jumpDepth);
        }
        else
        {
            jumpAdress->prev->leftShiftedErasureJumpPointShiftNoSegmentSizeDecrease(erasureIndex, size/2, jumpDepth);
        }
    }

    // Called to shift the jump nodes after an element has been erased from the Pral, and the Sub-Pral (the section of the Pral covered by the jump tree rooted at this) is set
    // to decrease in size by 1. erasureIndex is the index of the erased element within the Sub-Pral, size is the number of elements in the Sub-Pral (before the erasure), and
    // jumpDepth is the remaining height in the jump tree.
    void erasureJumpPointShift(unsigned int erasureIndex, unsigned int size, short jumpDepth)
    {
        if(jumpDepth == 0) return;
        jumpDepth --;
        
        if(erasureIndex >= size/2)// the position of the index is not affecting anything here.
        {
            if(size % 2)// size % 2 == 1.
            {
                jumpAdress->erasureJumpPointShift(erasureIndex - (size/2), (size + 1) / 2, jumpDepth);
            }
            else// size % 2 == 0.
            {
                jumpAdress->prev->prev->jumpAdress = jumpAdress->prev->jumpAdress;
                jumpAdress->prev->jumpAdress = jumpAdress->jumpAdress;
                jumpAdress->jumpAdress = NULL;

                jumpAdress = jumpAdress->prev;

                jumpAdress->prev->erasureJumpPointShift(erasureIndex, size/2, jumpDepth);

                if(erasureIndex < size) jumpAdress->leftShiftedErasureJumpPointShiftNoSegmentSizeDecrease(erasureIndex - (size/2), (size + 1) / 2, jumpDepth);
                else jumpAdress->shiftAllLeftByOne(jumpDepth);
            }
        }
        else// erasureIndex < size/2. Right shift required.
        {
            if(size % 2)// size % 2 == 1.
            {
                jumpAdress->next->jumpAdress = jumpAdress->jumpAdress;
                jumpAdress->jumpAdress = jumpAdress->prev->jumpAdress;
                jumpAdress->prev->jumpAdress = NULL;

                jumpAdress = jumpAdress->next;

                jumpAdress->erasureJumpPointShift(0, (size + 1) / 2, jumpDepth);

                jumpAdress->prev->erasureJumpPointShiftNoSegmentSizeDecrease(erasureIndex, size/2, jumpDepth);
            }
            else// size % 2 == 0.
            {
                jumpAdress->prev->erasureJumpPointShift(erasureIndex, size/2, jumpDepth);
            }
        }
    }
};

// Used for tracking the indecies of nodes referenced by a PralIndexedIterator. Not intended for direct use.
struct PralIndexListNode
{
    PralIndexListNode * prev = NULL;
    PralIndexListNode * next = NULL;
    unsigned int index;
    bool active = true;// While true, it means that there is an accosiated PralIndexedIterator with this node.
    bool abandoned = false;// set to true if the relavent PRAL is cleared or deleted. When True, this means connections don't matter, and PralIndexedIterators should handle destroying them (instead of leaving it to the pral)

    PralIndexListNode(PralIndexListNode * inPrev, PralIndexListNode * inNext, unsigned int inIndex)
    {
        prev = inPrev;
        index = inIndex;
        next = inNext;

        if(prev) prev->next = this;
        if(next) next->prev = this;
    }
};

// When inserting or erasing an element from the pral, that element's index is required to shift the jump tree around. PralIndexedIterator contains a pointer to a node in a Pral
// and automatically keeps track of the node's index for this purpose. The index remains accurate after insertions and erasures.
template <typename T>
class PralIndexedIterator
{
    private:
        PralIndexListNode * indexSource;
        PralNode<T> * referencedNode;

        // deletes indexSource or sets it to be deleted by the relavant PRAL
        void dereferenceIndex()
        {
            if(!indexSource)
            {
                return;
            }

            if(indexSource->abandoned)
            {
                delete indexSource;
                return;
            }

            if(indexSource->prev)
            {
                if(indexSource->next)
                {
                    indexSource->next->prev = indexSource->prev;
                }
                
                indexSource->prev->next = indexSource->next;
                delete indexSource;
            }
            else
            {
                indexSource->active = false;
            }
        }

    public:
        PralIndexedIterator(PralIndexListNode * inIndexSource = NULL, PralNode<T> * inReferencedNode = NULL)
        {
            indexSource = inIndexSource;
            referencedNode = inReferencedNode;
        }

        ~PralIndexedIterator()
        {
            dereferenceIndex();
        }

        void operator=(PralIndexedIterator<T> const & input)
        {
            referencedNode = input.referencedNode;

            dereferenceIndex();

            new PralIndexListNode(input.indexSource, input.indexSource->next, input.indexSource->index);

            indexSource = input.indexSource->next;
        }

        void forward()
        {
            indexSource->index ++;
            referencedNode = referencedNode->next;
        }

        void backward()
        {
            indexSource->index --;
            referencedNode = referencedNode->prev;
        }

        PralIndexedIterator<T> next(int distance = 1)
        {
            PralIndexListNode * newIndexListNode = new PralIndexListNode(indexSource, indexSource->next, indexSource->index + distance);

            PralNode<T> * targetNode = referencedNode;

            for(int i = 0; i < distance; i++)
            {
                targetNode = targetNode->next;
            }

            return PralIndexedIterator<T>(newIndexListNode, targetNode);
        }

        PralIndexedIterator<T> prev(int distance = 1)
        {
            PralIndexListNode * newIndexListNode = new PralIndexListNode(indexSource, indexSource->next, indexSource->index - distance);

            PralNode<T> * targetNode = referencedNode;

            for(int i = 0; i < distance; i++)
            {
                targetNode = targetNode->prev;
            }

            return PralIndexedIterator<T>(newIndexListNode, targetNode);
        }

        PralNode<T> * getNode()
        {
            return referencedNode;
        }

        unsigned int getIndex()
        {
            return indexSource->index;
        }

        T getValue()
        {
            return referencedNode->value;
        }

        void setValue(T in)
        {
            referencedNode->value = in;
        }
};

template <typename T>
class Pral
{
    private:
        PralNode<T> * first = NULL;
        PralNode<T> * last = NULL;
        short walkDistance;
        short jumpDepth;
        unsigned int sizeVar;
        PralIndexListNode * indexListHead = NULL;
        
        // The calculation that determines the depth of the binary tree of jump-nodes works by minimising
        // (the maximum walk distance from a node to the nearest jump node) + ((the total number of jump-nodes in the binary tree) * (totalJumpPointsInefficiencyMod)) + ((the depth of the binary tree of jump-nodes) * (jumpDepthInefficiencyMod).
        float totalJumpPointsInefficiencyMod;
        float jumpDepthInefficiencyMod;

        void emptyInsert(T value)
        {
            first = new PralNode<T>(value);
            last = first;

            sizeVar = 1;

            walkDistance = 0;

            jumpDepth = 0;
        }

        void oneElementErase()
        {
            delete first;
            first = NULL;
            last = NULL;

            sizeVar = 0;

            walkDistance = 0;

            jumpDepth = 0;
        }

        void indexListShiftInsertion(unsigned int insertionIndex)
        {
            PralIndexListNode * iterator = indexListHead;

            if(indexListHead && !indexListHead->active)
            {
                iterator = indexListHead->next;
                delete indexListHead;
                indexListHead = iterator;

                if(indexListHead)
                {
                    indexListHead->prev = NULL;
                }
            }

            while(iterator != NULL)
            {
                if(iterator->index >= insertionIndex) iterator->index ++;

                iterator = iterator->next;
            }
        }

        void indexListShiftErasure(unsigned int erasureIndex)
        {
            PralIndexListNode * iterator = indexListHead;

            if(indexListHead && !indexListHead->active)
            {
                iterator = indexListHead->next;
                delete indexListHead;
                indexListHead = iterator;

                if(indexListHead)
                {
                    indexListHead->prev = NULL;
                }
            }

            while(iterator != NULL)
            {
                if(iterator->index > erasureIndex) iterator->index --;

                iterator = iterator->next;
            }
        }

    public:
        Pral (float totalJumpPointsInefficiencyModArg = 3, float jumpDepthInefficiencyModArg = 2)
        {
            sizeVar = 0;
            walkDistance = 0;
            jumpDepth = 0;
            totalJumpPointsInefficiencyMod = totalJumpPointsInefficiencyModArg;
            jumpDepthInefficiencyMod = jumpDepthInefficiencyModArg;
        }
        
        Pral (std::initializer_list<T> const & input, float totalJumpPointsInefficiencyModArg = 3, float jumpDepthInefficiencyModArg = 2)
        {
            PralNode<T> * iterationNode;
            float floatWalkDist;
            short numTreeElements;
            short positionInArray = 0;
            int iterationStartPosition = 1;

            totalJumpPointsInefficiencyMod = totalJumpPointsInefficiencyModArg;
            jumpDepthInefficiencyMod = jumpDepthInefficiencyModArg;

            sizeVar = input.size();

            if(sizeVar == 0)
            {
                walkDistance = 0;
                jumpDepth = 0;
                return;
            }
            if(sizeVar == 1)
            {
                first = new PralNode<T>(*input.begin());
                last = first;
                walkDistance = 0;
                jumpDepth = 0;
                return;
            }
            
            floatWalkDist = (2*totalJumpPointsInefficiencyMod*sizeVar) / (sqrt((jumpDepthInefficiencyMod*jumpDepthInefficiencyMod/0.48045301391/*ln(2)^2*/) + (4*totalJumpPointsInefficiencyMod*sizeVar)) - (jumpDepthInefficiencyMod/0.693147180561/*ln(2)*/)) - 1;

            if(floatWalkDist < 2) floatWalkDist = 2;
            if(floatWalkDist > sizeVar/2) floatWalkDist = sizeVar/2;

            jumpDepth = (short)ceil(log2(sizeVar / (2 * floatWalkDist + 2)));
            
            if(jumpDepth < 0) jumpDepth = 0;

            walkDistance = (short)ceil(sizeVar / (pow(2, 1 + jumpDepth))) - 1;

            numTreeElements = (short)pow(2, jumpDepth);
            
            first = new PralNode<T>(*input.begin());

            // Creating binary tree:

            int * jumpPrevIndecies = new int[numTreeElements];

            PralNode<T> * * jumpPrevAdresses = new PralNode<T>*[numTreeElements];

            first->createTree(input, sizeVar, 0, jumpDepth, jumpPrevIndecies, jumpPrevAdresses, &positionInArray, 0);

            last = new PralNode<T>(*(input.end() - 1));

            jumpPrevIndecies[numTreeElements - 1] = sizeVar - 1;
            jumpPrevAdresses[numTreeElements - 1] = last;

            // filling in space between jumpNodes

            iterationNode = first;

            for(int i = 0; i < numTreeElements; i++)
            {
                for(int j = iterationStartPosition; j < jumpPrevIndecies[i]; j++)
                {
                    iterationNode->next = new PralNode<T>(*(input.begin() + j), iterationNode);
                    iterationNode = iterationNode->next;
                }

                iterationNode->next = jumpPrevAdresses[i];
                jumpPrevAdresses[i]->prev = iterationNode;
                iterationNode = jumpPrevAdresses[i]->next;

                
                iterationStartPosition = jumpPrevIndecies[i] + 2;
            }

            delete[] jumpPrevIndecies;
            delete[] jumpPrevAdresses;
        }

        Pral (T input[], unsigned int size, float totalJumpPointsInefficiencyModArg = 3, float jumpDepthInefficiencyModArg = 2)
        {
            PralNode<T> * iterationNode;
            float floatWalkDist;
            short numTreeElements;
            short positionInArray = 0;
            int iterationStartPosition = 1;

            totalJumpPointsInefficiencyMod = totalJumpPointsInefficiencyModArg;
            jumpDepthInefficiencyMod = jumpDepthInefficiencyModArg;

            sizeVar = size;

            if(sizeVar == 0)
            {
                walkDistance = 0;
                jumpDepth = 0;
                return;
            }
            if(sizeVar == 1)
            {
                first = new PralNode<T>(input[0]);
                last = first;
                walkDistance = 0;
                jumpDepth = 0;
                return;
            }
            
            floatWalkDist = (2*totalJumpPointsInefficiencyMod*sizeVar) / (sqrt((jumpDepthInefficiencyMod*jumpDepthInefficiencyMod/0.48045301391/*ln(2)^2*/) + (4*totalJumpPointsInefficiencyMod*sizeVar)) - (jumpDepthInefficiencyMod/0.693147180561/*ln(2)*/)) - 1;

            if(floatWalkDist < 2) floatWalkDist = 2;
            if(floatWalkDist > sizeVar/2) floatWalkDist = sizeVar/2;

            jumpDepth = (short)ceil(log2(sizeVar / (2 * floatWalkDist + 2)));
            
            if(jumpDepth < 0) jumpDepth = 0;

            walkDistance = (short)ceil(sizeVar / (pow(2, 1 + jumpDepth))) - 1;

            numTreeElements = (short)pow(2, jumpDepth);
            
            first = new PralNode<T>(input[0]);

            // Creating binary tree:

            int * jumpPrevIndecies = new int[numTreeElements];

            PralNode<T> * * jumpPrevAdresses = new PralNode<T>*[numTreeElements];

            first->createTree(input, sizeVar, 0, jumpDepth, jumpPrevIndecies, jumpPrevAdresses, &positionInArray, 0);

            last = new PralNode<T>(input[size - 1]);

            jumpPrevIndecies[numTreeElements - 1] = sizeVar - 1;
            jumpPrevAdresses[numTreeElements - 1] = last;

            // filling in space between jumpNodes

            iterationNode = first;

            for(int i = 0; i < numTreeElements; i++)
            {
                for(int j = iterationStartPosition; j < jumpPrevIndecies[i]; j++)
                {
                    iterationNode->next = new PralNode<T>(input[j], iterationNode);
                    iterationNode = iterationNode->next;
                }

                iterationNode->next = jumpPrevAdresses[i];
                jumpPrevAdresses[i]->prev = iterationNode;
                iterationNode = jumpPrevAdresses[i]->next;

                
                iterationStartPosition = jumpPrevIndecies[i] + 2;
            }

            delete[] jumpPrevIndecies;
            delete[] jumpPrevAdresses;
        }

        void clear()
        {
            while(last != NULL)
            {
                last = first->next;
                delete first;
                first = last;
            }

            if(indexListHead != NULL)
            {
                if(!indexListHead->active)
                {
                    PralIndexListNode * tempHead = indexListHead->next;
                    delete indexListHead;
                    indexListHead = tempHead;
                }

                while(indexListHead != NULL)
                {
                    indexListHead->abandoned = true;
                    indexListHead = indexListHead->next;
                }
            }

            sizeVar = 0;
            walkDistance = 0;
            jumpDepth = 0;
        }

        ~Pral()
        {
            clear();
        }

        PralNode<T> * jumpToNode(unsigned int targetIndex)
        {
            PralNode<T> * returnNode;

            if(targetIndex >= sizeVar) return last->next->next;

            if(sizeVar - 1 - walkDistance <= targetIndex)
            {
                returnNode = last;

                for(unsigned int i = sizeVar - 1; i > targetIndex; i--)
                {
                    returnNode = returnNode->prev;
                }

                return returnNode;
            }

            return first->jumpToNode(targetIndex, sizeVar, walkDistance, true);
        }

        void insertAfter(T value, PralNode<T> * beforeInsertedNode, unsigned int insertionIndex)
        {
            if(beforeInsertedNode == last)
            {
                pushBack(value);
                return;
            }

            short newJumpDepth;
            PralNode<T> * insertedNode = new PralNode<T>(value);
            float floatWalkDist;
            
            insertedNode->next = beforeInsertedNode->next;
            beforeInsertedNode->next->prev = insertedNode;

            insertedNode->prev = beforeInsertedNode;
            beforeInsertedNode->next = insertedNode;

            if(beforeInsertedNode->jumpAdress && beforeInsertedNode->prev && !beforeInsertedNode->prev->jumpAdress)
            {
                insertedNode->jumpAdress = beforeInsertedNode->jumpAdress;
                beforeInsertedNode->jumpAdress = NULL;
            }

            first->insertionJumpPointShift(insertionIndex, sizeVar, jumpDepth);

            sizeVar ++;

            floatWalkDist = (2*totalJumpPointsInefficiencyMod*sizeVar) / (sqrt((jumpDepthInefficiencyMod*jumpDepthInefficiencyMod/0.48045301391/*ln(2)^2*/) + (4*totalJumpPointsInefficiencyMod*sizeVar)) - (jumpDepthInefficiencyMod/0.693147180561/*ln(2)*/)) - 1;
            
            if(floatWalkDist < 2) floatWalkDist = 2;
            if(floatWalkDist > sizeVar/2) floatWalkDist = sizeVar/2;

            newJumpDepth = (short)ceil(log2((float)sizeVar / (2 * floatWalkDist + 2)));

            if(newJumpDepth < 0) newJumpDepth = 0;

            walkDistance = (short)ceil(sizeVar / (pow(2, 1 + newJumpDepth))) - 1;

            if(newJumpDepth != jumpDepth)
            {
                jumpDepth = newJumpDepth;

                first->addJumpPointLayer(sizeVar * 2, jumpDepth, true);
            }

            indexListShiftInsertion(insertionIndex);
        }

        void insertAfter(T value, PralIndexedIterator<T> & reference)
        {
            insertAfter(value, reference.getNode(), reference.getIndex() + 1);
        }

        void insertBefore(T value, PralIndexedIterator<T> & reference)
        {
            PralNode<T> * node = reference.getNode();
            
            if(node == first)
            {
                pushFront(value);
                return;
            }

            insertAfter(value, node->prev, reference.getIndex());
        }

        void pushFront(T value)
        {
            if(sizeVar == 0)
            {
                emptyInsert(value);
                return;
            }
            
            PralNode<T>* newNode = new PralNode<T>(value);
            short newJumpDepth;
            float floatWalkDist;

            first->prev = newNode;
            newNode->next = first;
            newNode->jumpAdress = first->jumpAdress;
            first->jumpAdress = NULL;
            first = newNode;

            first->insertionJumpPointShift(0, sizeVar, jumpDepth);

            sizeVar ++;

            floatWalkDist = (2*totalJumpPointsInefficiencyMod*sizeVar) / (sqrt((jumpDepthInefficiencyMod*jumpDepthInefficiencyMod/0.48045301391/*ln(2)^2*/) + (4*totalJumpPointsInefficiencyMod*sizeVar)) - (jumpDepthInefficiencyMod/0.693147180561/*ln(2)*/)) - 1;
            
            if(floatWalkDist < 2) floatWalkDist = 2;
            if(floatWalkDist > sizeVar/2) floatWalkDist = sizeVar/2;

            newJumpDepth = (short)ceil(log2((float)sizeVar / (2 * floatWalkDist + 2)));

            if(newJumpDepth < 0) newJumpDepth = 0;

            walkDistance = (short)ceil(sizeVar / (pow(2, 1 + newJumpDepth))) - 1;

            if(newJumpDepth != jumpDepth)
            {
                jumpDepth = newJumpDepth;

                first->addJumpPointLayer(sizeVar * 2, jumpDepth, true);
            }

            indexListShiftInsertion(0);
        }

        void pushBack(T value)
        {
            if(sizeVar == 0)
            {
                emptyInsert(value);
                return;
            }
            
            PralNode<T>* newNode = new PralNode<T>(value);
            short newJumpDepth;
            float floatWalkDist;

            last->next = newNode;
            newNode->prev = last;
            last = newNode;

            first->insertionJumpPointShift(sizeVar, sizeVar, jumpDepth);

            sizeVar ++;

            floatWalkDist = (2*totalJumpPointsInefficiencyMod*sizeVar) / (sqrt((jumpDepthInefficiencyMod*jumpDepthInefficiencyMod/0.48045301391/*ln(2)^2*/) + (4*totalJumpPointsInefficiencyMod*sizeVar)) - (jumpDepthInefficiencyMod/0.693147180561/*ln(2)*/)) - 1;
            
            if(floatWalkDist < 2) floatWalkDist = 2;
            if(floatWalkDist > sizeVar/2) floatWalkDist = sizeVar/2;

            newJumpDepth = (short)ceil(log2((float)sizeVar / (2 * floatWalkDist + 2)));

            if(newJumpDepth < 0) newJumpDepth = 0;

            walkDistance = (short)ceil(sizeVar / (pow(2, 1 + newJumpDepth))) - 1;
            
            if(newJumpDepth != jumpDepth)
            {
                jumpDepth = newJumpDepth;

                first->addJumpPointLayer(sizeVar * 2, jumpDepth, true);
            }
        }

        void insert(unsigned int index, T value)
        {
            if(index == 0)
            {
                pushFront(value);
            }
            else if(index == sizeVar)
            {
                pushBack(value);
            }
            else
            {
                insertAfter(value, jumpToNode(index - 1), index);
            }
        }

        void popFront()
        {
            if(sizeVar == 1)
            {
                oneElementErase();
                return;
            }

            short newJumpDepth;
            float floatWalkDist;
            
            first->next->jumpAdress = first->jumpAdress;
            first = first->next;
            delete first->prev;
            first->prev = NULL;

            first->erasureJumpPointShift(0, sizeVar, jumpDepth);

            sizeVar --;

            floatWalkDist = (2*totalJumpPointsInefficiencyMod*sizeVar) / (sqrt((jumpDepthInefficiencyMod*jumpDepthInefficiencyMod/0.48045301391/*ln(2)^2*/) + (4*totalJumpPointsInefficiencyMod*sizeVar)) - (jumpDepthInefficiencyMod/0.693147180561/*ln(2)*/)) - 1;
            
            if(floatWalkDist < 2) floatWalkDist = 2;
            if(floatWalkDist > sizeVar/2) floatWalkDist = sizeVar/2;

            newJumpDepth = (short)ceil(log2((float)sizeVar / (2 * floatWalkDist + 2)));

            if(newJumpDepth < 0) newJumpDepth = 0;

            walkDistance = (short)ceil(sizeVar / (pow(2, 1 + newJumpDepth))) - 1;

            if(newJumpDepth != jumpDepth)
            {
                jumpDepth = newJumpDepth;

                first->removeJumpPointLayer(jumpDepth);
            }

            indexListShiftErasure(0);
        }

        void popBack()
        {
            if(sizeVar == 1)
            {
                oneElementErase();
                return;
            }

            short newJumpDepth;
            float floatWalkDist;

            last = last->prev;
            delete last->next;
            last->next = NULL;

            first->erasureJumpPointShift(sizeVar - 1, sizeVar, jumpDepth);

            sizeVar --;

            floatWalkDist = (2*totalJumpPointsInefficiencyMod*sizeVar) / (sqrt((jumpDepthInefficiencyMod*jumpDepthInefficiencyMod/0.48045301391/*ln(2)^2*/) + (4*totalJumpPointsInefficiencyMod*sizeVar)) - (jumpDepthInefficiencyMod/0.693147180561/*ln(2)*/)) - 1;
            
            if(floatWalkDist < 2) floatWalkDist = 2;
            if(floatWalkDist > sizeVar/2) floatWalkDist = sizeVar/2;

            newJumpDepth = (short)ceil(log2((float)sizeVar / (2 * floatWalkDist + 2)));

            if(newJumpDepth < 0) newJumpDepth = 0;

            walkDistance = (short)ceil(sizeVar / (pow(2, 1 + newJumpDepth))) - 1;

            if(newJumpDepth != jumpDepth)
            {
                jumpDepth = newJumpDepth;

                first->removeJumpPointLayer(jumpDepth);
            }
        }

        void erase(PralNode<T> * eraseNode, unsigned int erasureIndex)
        {
            if(erasureIndex == sizeVar - 1)
            {
                popBack();
                return;
            }
            if(erasureIndex == 0)
            {
                popFront();
                return;
            }

            short newJumpDepth;
            int numSegments = pow(2, jumpDepth);
            PralNode<T> * parent = first->searchTreeForParent(erasureIndex, sizeVar, walkDistance);
            float floatWalkDist;

            if(parent)
            {
                parent->jumpAdress = parent->jumpAdress->next;
                
                if(eraseNode->jumpAdress)
                {
                    eraseNode->next->jumpAdress = eraseNode->jumpAdress;
                    eraseNode->jumpAdress = NULL;
                }
            }
            else if(eraseNode->jumpAdress)
            {
                eraseNode->prev->jumpAdress = eraseNode->jumpAdress;
            }

            eraseNode->prev->next = eraseNode->next;
            eraseNode->next->prev = eraseNode->prev;

            delete eraseNode;

            first->erasureJumpPointShift(erasureIndex, sizeVar, jumpDepth);

            sizeVar --;

            floatWalkDist = (2*totalJumpPointsInefficiencyMod*sizeVar) / (sqrt((jumpDepthInefficiencyMod*jumpDepthInefficiencyMod/0.48045301391/*ln(2)^2*/) + (4*totalJumpPointsInefficiencyMod*sizeVar)) - (jumpDepthInefficiencyMod/0.693147180561/*ln(2)*/)) - 1;
            
            if(floatWalkDist < 2) floatWalkDist = 2;
            if(floatWalkDist > sizeVar/2) floatWalkDist = sizeVar/2;

            newJumpDepth = (short)ceil(log2((float)sizeVar / (2 * floatWalkDist + 2)));

            if(newJumpDepth < 0) newJumpDepth = 0;

            walkDistance = (short)ceil(sizeVar / (pow(2, 1 + newJumpDepth))) - 1;

            if(newJumpDepth != jumpDepth)
            {
                jumpDepth = newJumpDepth;

                first->removeJumpPointLayer(jumpDepth);
            }

            indexListShiftErasure(erasureIndex);
        }

        void erase(PralIndexedIterator<T> & reference)
        {
            erase(reference.getNode(), reference.getIndex());
        }

        void erase(unsigned int index)
        {
            if(index == 0)
            {
                popFront();
            }
            else if(index == sizeVar - 1)
            {
                popBack();
            }
            else
            {
                erase(jumpToNode(index), index);
            }
        }

        PralIndexedIterator<T> getIndexedIterator(unsigned int index)
        {
            if(indexListHead)
            {
                new PralIndexListNode(indexListHead, indexListHead->next, index);

                return PralIndexedIterator<T>(indexListHead->next, jumpToNode(index));
            }
            else
            {
                indexListHead = new PralIndexListNode(NULL, NULL, index);

                return PralIndexedIterator<T>(indexListHead, jumpToNode(index));
            }
        }

        PralIndexedIterator<T> getIndexedIterator(PralNode<T> * node, unsigned int index)
        {
            if(indexListHead)
            {
                new PralIndexListNode(indexListHead, indexListHead->next, index);

                return PralIndexedIterator<T>(indexListHead->next, node);
            }
            else
            {
                indexListHead = new PralIndexListNode(NULL, NULL, index);

                return PralIndexedIterator<T>(indexListHead, node);
            }
        }

        void operator=(Pral<T> const & input)
        {
            PralNode<T> * iterationNode;
            PralNode<T> * inputIterationNode;
            short numTreeElements;
            short positionInArray = 0;
            int iterationStartPosition = 1;

            while(last != NULL)
            {
                last = first->next;
                delete first;
                first = last;
            }
            if(indexListHead != NULL)
            {
                while(indexListHead->next != NULL)
                {
                    indexListHead = indexListHead->next;
                    delete indexListHead->prev;
                }

                delete indexListHead;
            }

            totalJumpPointsInefficiencyMod = input.totalJumpPointsInefficiencyMod;
            jumpDepthInefficiencyMod = input.jumpDepthInefficiencyMod;
            walkDistance = input.walkDistance;
            jumpDepth = input.jumpDepth;
            sizeVar = input.sizeVar;

            if(sizeVar == 0)
            {
                return;
            }
            if(sizeVar == 1)
            {
                first = new PralNode<T>(input.first->value);
                last = first;
                return;
            }

            numTreeElements = (short)pow(2, jumpDepth);
            
            first = new PralNode<T>(input.first->value);

            // Creating binary tree:

            int * jumpPrevIndecies = new int[numTreeElements];

            PralNode<T> * * jumpPrevAdresses = new PralNode<T>*[numTreeElements];

            first->createTree(input.first, sizeVar, 0, jumpDepth, jumpPrevIndecies, jumpPrevAdresses, &positionInArray, 0);

            last = new PralNode<T>(input.last->value);

            jumpPrevIndecies[numTreeElements - 1] = sizeVar - 1;
            jumpPrevAdresses[numTreeElements - 1] = last;

            // filling in space between jumpNodes

            iterationNode = first;
            inputIterationNode = input.first;

            for(int i = 0; i < numTreeElements; i++)
            {
                for(int j = iterationStartPosition; j < jumpPrevIndecies[i]; j++)
                {
                    inputIterationNode = inputIterationNode->next;

                    iterationNode->next = new PralNode<T>(inputIterationNode->value, iterationNode);
                    iterationNode = iterationNode->next;
                }

                iterationNode->next = jumpPrevAdresses[i];
                jumpPrevAdresses[i]->prev = iterationNode;
                iterationNode = jumpPrevAdresses[i]->next;

                inputIterationNode = inputIterationNode->next->next;
                iterationStartPosition = jumpPrevIndecies[i] + 2;
            }

            delete[] jumpPrevIndecies;
            delete[] jumpPrevAdresses;
        }

        T& operator[](unsigned int index)
        {
            return jumpToNode(index)->value;
        }

        unsigned int size()
        {
            return sizeVar;
        }
};
