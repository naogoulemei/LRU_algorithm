/* 
LRU算法会将近期最不会访问的数据淘汰掉，LRU如此流行的原因是实现比较简单，而且对于实际问题也很实用，良好的运行时性能，命中率较高。
 	使用链表实现
 	新数据插入到链表头部。
 	每当缓存命中（既缓存数据被访问），则将数据移到链表头部
 	当链表满的时候，将链表尾部的数据丢弃
LRU实现采用双向链表+Map 来进行实现，这里采用双向链表的原因是：如果采用普通的单链表，则删除节点的时候需要从表头开始遍历查找、效率为O(n)采用双向链表可以直接改变节点的前驱的指针指向进行删除达到O(1)，使用Map来保存节点的key,value值便于能在O(logN)的时间查找元素，对应get操作。
*/

///双链表节点的定义
struct CacheNode
{
    int key;//键
    int value;//值
    CacheNode *pre, *next;//节点的前驱，后继指针
    CacheNode(int k,int v):key(k),value(v),pre(NULL),next(NULL){}
};

///对于LRUCache这个类而言，构造函数需要指定容量大小

LRUCache(int capacity)
{
    size= capacity;//容量
    head= NULL;  //链表头指针
    tail=NULL ; // 链表尾指针
}
///双链表的节点删除操作

void Remove(CacheNode *node)
{
    if(node->pre!=NULL)
    {
        node->pre->next=node->next;
    }
    else
    {
        head=node->next;
    }
    if(node->next!=NULL)
    {
        node->next->pre=node->pre;
    }
    else
    {
        tail=node->pre;
    }
}
///将节点插入到头部的操作
void setHead(CacheNode* node)
{
    node->next=head;
    node->pre=NULL;

    if(head!=NULL)
        head->pre=node;
    head=node;
    if(tail==NULL)
        tail=head;
}
///get(key)操作的实现比较简单，直接通过判断Map是否含有key值即可，如果查找到key
///则返回对应的value，否则返回-1

int get(int key)
{
    map<int,CacheNode*>::iterator it=mp.find(key);
    if(it!=mp.end())
    {
        CacheNode *node=it->second;
        Remove(node);
        setHead(node);
        return node->value;
    }
    else
    {
        return -1;
    }
}
///set(key,value)操作需要分情况判断。如果当前的key值对应的节点已经存在，
///则将这个节点取出来,并且删除节点所处的原有的位置，并在头部插入该节点；
///如果节点不存在，这个时候需要在链表的头部插入新节点，插入新节点可能导致容量溢出
///如果出现溢出的情况，则需要删除链表尾部的节点。

void set(int key,int value)
{
    map<int,CacheNode*>::iterator it=mp.find(key);
    if(it!=mp.end())
    {
        CacheNode* node=it->second;
        node->value=value;
        Remove(node);
        setHead(node);
    }
    else
    {
        CacheNode *newNode=new CacheNode(key,value);
        if(mp.size()>=size)
        {
            map<int,CacheNode*>::iterator iter=mp.find(tail->key);
            remove(tail);
            mp.erase(iter);
        }
        setHead(newNode);
        mp[key]=newNode;
    }
}


