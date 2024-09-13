template <typename T>
struct SBBTreeNode
{
    T value;

    SBBTreeNode<T> * left = NULL;
    SBBTreeNode<T> * right = NULL;
    
    bool isLeft;// Go back over functions and make this get updated.
    SBBTreeNode<T> * above;// neccessary for iteration to be allowed
    
    int numNodes = 1;// in subtree, including this.
    int height = 1;

    SBBTreeNode(T valueArg, bool isLeftArg = false, SBBTreeNode<T> * aboveArg = NULL)
    {
        value = valueArg;
        isLeft = isLeftArg;
        above = aboveArg;
    }

    ~SBBTreeNode()
    {
        if(left) delete left;
        if(right) delete right;
    }

    void updateNumNodesAndHeight()
    {
        numNodes = (right ? right->numNodes : 0) + (left ? left->numNodes : 0) + 1;
        height = std::max((right ? right->height : 0), (left ? left->height : 0)) + 1;
    }

    int getBalanceFactor()
    {
        return (right ? right->height : 0) - (left ? left->height : 0);
    }

    void rotateLeftNoValueUpdate()
    {
        right->above = above;

        above = right;
        right = above->left;
        
        if(right)
        {
            right->above = this;
            right->isLeft = false;
        }

        above->left = this;

        above->isLeft = isLeft;
        isLeft = true;
    }

    void rotateRightNoValueUpdate()
    {
        left->above = above;

        above = left;
        left = above->right;

        if(left)
        {
            left->above = this;
            left->isLeft = true;
        }

        above->right = this;

        above->isLeft = isLeft;
        isLeft = false;
    }

    SBBTreeNode<T> * rotateLeft()
    {
        rotateLeftNoValueUpdate();

        updateNumNodesAndHeight();
        above->updateNumNodesAndHeight();

        return above;
    }

    SBBTreeNode<T> * rotateRight()
    {
        rotateRightNoValueUpdate();

        updateNumNodesAndHeight();
        above->updateNumNodesAndHeight();

        return above;
    }

    SBBTreeNode<T> * rotateRightLeft()
    {
        right->rotateRightNoValueUpdate();
        right = right->above;

        rotateLeftNoValueUpdate();

        updateNumNodesAndHeight();
        above->right->updateNumNodesAndHeight();
        above->updateNumNodesAndHeight();

        return above;
    }

    SBBTreeNode<T> * rotateLeftRight()
    {
        left->rotateLeftNoValueUpdate();
        left = left->above;

        rotateRightNoValueUpdate();

        updateNumNodesAndHeight();
        above->left->updateNumNodesAndHeight();
        above->updateNumNodesAndHeight();

        return above;
    }

    SBBTreeNode<T> * accessAtIndex(unsigned int index)
    {
        if(left)
        {
            if(index < left->numNodes) return left->accessAtIndex(index);
            else if(index > left->numNodes) return right->accessAtIndex(index - left->numNodes - 1);
            
            return this;
        }
        else
        {
            if(index == 0) return this;

            return right->accessAtIndex(index - 1);
        }
    }

    SBBTreeNode<T> * balanceAndUpdateNumNodesAndHeight(bool nodeInserted)// paramater for insertion vs deletion.
    {
        updateNumNodesAndHeight();

        if(getBalanceFactor() == 2)
        {
            if(right->getBalanceFactor() == -1)
            {
                if(above)
                {
                    if(isLeft)
                    {
                        above->left = rotateRightLeft();
                    }
                    else
                    {
                        above->right = rotateRightLeft();
                    }
                }
                else
                {
                    return rotateRightLeft();
                }
            }
            else
            {
                if(above)
                {
                    if(isLeft)
                    {
                        above->left = rotateLeft();
                    }
                    else
                    {
                        above->right = rotateLeft();
                    }
                }
                else
                {
                    return rotateLeft();
                }
            }

            if(nodeInserted) return above->recursiveUpdateNumNodesAndHeight();
        }
        else if(getBalanceFactor() == -2)
        {
            if(left->getBalanceFactor() == 1)
            {
                if(above)
                {
                    if(isLeft)
                    {
                        above->left = rotateLeftRight();
                    }
                    else
                    {
                        above->right = rotateLeftRight();
                    }
                }
                else
                {
                    return rotateLeftRight();
                }
            }
            else
            {
                if(above)
                {
                    if(isLeft)
                    {
                        above->left = rotateRight();
                    }
                    else
                    {
                        above->right = rotateRight();
                    }
                }
                else
                {
                    return rotateRight();
                }
            }

            if(nodeInserted) return above->recursiveUpdateNumNodesAndHeight();
        }

        if(above) return above->balanceAndUpdateNumNodesAndHeight(nodeInserted);
        
        return this;
    }

    SBBTreeNode<T> * recursiveUpdateNumNodesAndHeight()
    {
        updateNumNodesAndHeight();

        if(above) return above->recursiveUpdateNumNodesAndHeight();

        return this;
    }

    SBBTreeNode<T> * next()
    {
        if(right) return right->accessAtIndex(0);
        
        if(isLeft)
        {
            return above;
        }
        else
        {
            SBBTreeNode<T> * traversalNode = above;

            while(!traversalNode->isLeft)
            {
                traversalNode = traversalNode->above;
            }

            return traversalNode->above;
        }
    }
};

template <typename T>
class SBBTree// a bare bones self balancing binary tree (AVLTree specifically) modified to store linearly aranged elements, sorted or not, and allow for an iterator. A bunch of functionality that isn't needed for the example isn't implemented, and functionality that isn't being timed (such as tree creation) isn't optimised.
{
    public:
        SBBTreeNode<T> * root = NULL;

        SBBTree() {}

        ~SBBTree()
        {
            if(root) delete root;
        }

        int size()
        {
            if(root) return root->numNodes;

            return 0;
        }

        void insert(int index, T value)
        {
            if(!root)
            {
                root = new SBBTreeNode<T>(value);
            }
            else if (index == size())
            {
                SBBTreeNode<T> * traversalNode = root->accessAtIndex(index - 1);

                traversalNode->right = new SBBTreeNode<T>(value, false, traversalNode);

                root = traversalNode->balanceAndUpdateNumNodesAndHeight(true);
            }
            else
            {
                SBBTreeNode<T> * traversalNode = root->accessAtIndex(index);

                if(traversalNode->left)
                {
                    traversalNode = traversalNode->left->accessAtIndex(traversalNode->left->numNodes - 1);

                    traversalNode->right = new SBBTreeNode<T>(value, false, traversalNode);
                }
                else
                {
                    traversalNode->left = new SBBTreeNode<T>(value, true, traversalNode);
                }

                root = traversalNode->balanceAndUpdateNumNodesAndHeight(true);
            }
        }

        void erase(int index)
        {
            if(size() == 1)
            {
                delete root;
                root = NULL;

                return;
            }

            SBBTreeNode<T> * target = root->accessAtIndex(index);

            if(target->getBalanceFactor() < 0)// go left.
            {
                SBBTreeNode<T> * swapNode = target->left->accessAtIndex(target->left->numNodes - 1);

                if(swapNode->isLeft)// swapNode->above == target.
                {
                    swapNode->above = target->above;

                    if(target->isLeft)
                    {
                        if(swapNode->above) swapNode->above->left = swapNode;
                    }
                    else
                    {
                        swapNode->isLeft = false;
                        if(swapNode->above) swapNode->above->right = swapNode;
                    }

                    swapNode->right = target->right;
                    if(swapNode->right) swapNode->right->above = swapNode;


                    target->left = NULL;
                    target->right = NULL;
                    delete target;

                    root = swapNode->balanceAndUpdateNumNodesAndHeight(false);
                }
                else
                {
                    SBBTreeNode<T> * balanceStart = swapNode->above;

                    balanceStart->right = swapNode->left;

                    if(balanceStart->right)
                    {
                        balanceStart->right->above = balanceStart;
                        balanceStart->right->isLeft = false;
                    }

                    swapNode->above = target->above;
                    swapNode->right = target->right;
                    swapNode->left = target->left;

                    if(target->isLeft)
                    {
                        swapNode->isLeft = true;
                        if(swapNode->above) swapNode->above->left = swapNode;
                    }
                    else
                    {
                        swapNode->isLeft = false;
                        if(swapNode->above) swapNode->above->right = swapNode;
                    }

                    swapNode->right->above = swapNode;
                    swapNode->left->above = swapNode;

                    target->left = NULL;
                    target->right = NULL;
                    delete target;

                    root = balanceStart->balanceAndUpdateNumNodesAndHeight(false);
                }
            }
            else if(target->right)// go right.
            {
                SBBTreeNode<T> * swapNode = target->right->accessAtIndex(0);

                if(!swapNode->isLeft)// swapNode->above == target.
                {
                    swapNode->above = target->above;

                    if(target->isLeft)
                    {
                        swapNode->isLeft = true;
                        if(swapNode->above) swapNode->above->left = swapNode;
                    }
                    else
                    {
                        if(swapNode->above) swapNode->above->right = swapNode;
                    }

                    swapNode->left = target->left;
                    if(swapNode->left) swapNode->left->above = swapNode;


                    target->left = NULL;
                    target->right = NULL;
                    delete target;

                    root = swapNode->balanceAndUpdateNumNodesAndHeight(false);
                }
                else
                {
                    SBBTreeNode<T> * balanceStart = swapNode->above;

                    balanceStart->left = swapNode->right;

                    if(balanceStart->left)
                    {
                        balanceStart->left->above = balanceStart;
                        balanceStart->left->isLeft = true;
                    }

                    swapNode->above = target->above;
                    swapNode->right = target->right;
                    swapNode->left = target->left;

                    if(target->isLeft)
                    {
                        swapNode->isLeft = true;
                        if(swapNode->above) swapNode->above->left = swapNode;
                    }
                    else
                    {
                        swapNode->isLeft = false;
                        if(swapNode->above) swapNode->above->right = swapNode;
                    }

                    swapNode->right->above = swapNode;
                    swapNode->left->above = swapNode;

                    target->left = NULL;
                    target->right = NULL;
                    delete target;

                    root = balanceStart->balanceAndUpdateNumNodesAndHeight(false);
                }
            }
            else
            {
                SBBTreeNode<T> * balanceStart = target->above;

                if(target->isLeft)
                {
                    balanceStart->left = NULL;
                }
                else
                {
                    balanceStart->right = NULL;
                }

                delete target;

                balanceStart->balanceAndUpdateNumNodesAndHeight(false);
            }
        }

        T& operator[](unsigned int index)
        {
            return root->accessAtIndex(index)->value;
        }
};