#ifndef __watchpoint_H__
#define __watchpoint_H__
#include "common.hpp"
#define NR_WP 32
#include "expr.hpp"
typedef struct watchpointType
{
    int NO;
    struct watchpointType *next;
    struct watchpointType *pro;
    wchar_t oldValue;
    char exprStr[60];
} WP;

class watchpoint
{
private:
    WP wp_pool[NR_WP] = {};
    WP *head = NULL, *free_ = NULL;
    WP *new_wp();
    void free_wp(WP *wp);
    expr * Inexpr;
public:
    watchpoint(expr* Inexpr);
    ~watchpoint();
    void theaddwatch(char *args);
    bool deletewatch(int n);
    void displaywatch();
    bool ifchange();
};
#endif