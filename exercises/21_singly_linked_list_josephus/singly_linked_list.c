#include "singly_linked_list.h"

#include <stdlib.h>

// 全局头指针
static link head = NULL;

// 创建新节点
link make_node(unsigned char item) {
    link p = (link)malloc(sizeof(struct node));
    if (p != NULL) {
        p->item = item;
        p->next = NULL;
    }
    return p;
}

// 释放节点
void free_node(link p) { free(p); }

// 查找节点
link search(unsigned char key) {
    for (link p = head; p != NULL; p = p->next) {
        if (p->item == key) {
            return p;
        }
    }
    return NULL;
}

// 在链表头部插入节点
void insert(link p) {
    if (p != NULL) {
        p->next = head;
        head = p;
    }
}

// 删除指定节点
void delete_node(link p) {
    if (p == NULL) return;

    if (head == p) {
        head = head->next;
        free_node(p);
    } else {
        link prev = head;
        while (prev != NULL && prev->next != p) {
            prev = prev->next;
        }
        if (prev != NULL) {
            prev->next = p->next;
            free_node(p);
        }
    }
}

// 遍历链表
void traverse(void (*visit)(link)) {
    for (link p = head; p != NULL; p = p->next) {
        visit(p);
    }
}

// 销毁整个链表
void destroy(void) {
    link p = head;
    while (p != NULL) {
        link temp = p->next;
        free_node(p);
        p = temp;
    }
    head = NULL;
}

// 在链表头部推入节点
void push(link p) { insert(p); }

// 从链表头部弹出节点
link pop(void) {
    if (head == NULL) return NULL;
    link p = head;
    head = head->next;
    p->next = NULL;
    return p;
}

// 释放链表内存
void free_list(link list_head) {
    link p = list_head;
    while (p != NULL) {
        link temp = p->next;
        free_node(p);
        p = temp;
    }
}
