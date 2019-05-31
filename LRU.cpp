/* 
LRU�㷨�Ὣ���������ʵ�������̭����LRU������е�ԭ����ʵ�ֱȽϼ򵥣����Ҷ���ʵ������Ҳ��ʵ�ã����õ�����ʱ���ܣ������ʽϸߡ�
 	ʹ������ʵ��
 	�����ݲ��뵽����ͷ����
 	ÿ���������У��Ȼ������ݱ����ʣ����������Ƶ�����ͷ��
 	����������ʱ�򣬽�����β�������ݶ���
LRUʵ�ֲ���˫������+Map ������ʵ�֣��������˫�������ԭ���ǣ����������ͨ�ĵ�������ɾ���ڵ��ʱ����Ҫ�ӱ�ͷ��ʼ�������ҡ�Ч��ΪO(n)����˫���������ֱ�Ӹı�ڵ��ǰ����ָ��ָ�����ɾ���ﵽO(1)��ʹ��Map������ڵ��key,valueֵ��������O(logN)��ʱ�����Ԫ�أ���Ӧget������
*/

///˫����ڵ�Ķ���
struct CacheNode
{
    int key;//��
    int value;//ֵ
    CacheNode *pre, *next;//�ڵ��ǰ�������ָ��
    CacheNode(int k,int v):key(k),value(v),pre(NULL),next(NULL){}
};

///����LRUCache�������ԣ����캯����Ҫָ��������С

LRUCache(int capacity)
{
    size= capacity;//����
    head= NULL;  //����ͷָ��
    tail=NULL ; // ����βָ��
}
///˫����Ľڵ�ɾ������

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
///���ڵ���뵽ͷ���Ĳ���
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
///get(key)������ʵ�ֱȽϼ򵥣�ֱ��ͨ���ж�Map�Ƿ���keyֵ���ɣ�������ҵ�key
///�򷵻ض�Ӧ��value�����򷵻�-1

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
///set(key,value)������Ҫ������жϡ������ǰ��keyֵ��Ӧ�Ľڵ��Ѿ����ڣ�
///������ڵ�ȡ����,����ɾ���ڵ�������ԭ�е�λ�ã�����ͷ������ýڵ㣻
///����ڵ㲻���ڣ����ʱ����Ҫ�������ͷ�������½ڵ㣬�����½ڵ���ܵ����������
///���������������������Ҫɾ������β���Ľڵ㡣

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


