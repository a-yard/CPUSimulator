#include "../../../Include/watchpoint.hpp"

watchpoint::watchpoint(expr *expr)
{
    int i;
    for (i = 0; i < NR_WP; i++)
    {
        wp_pool[i].NO = i;
        wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
        if (i != 0)
            wp_pool[i].pro = &wp_pool[i - 1];
        else
            wp_pool[i].pro = NULL;
    }

    head = NULL;
    free_ = wp_pool;
    //init
    this->Inexpr = expr;
}

watchpoint::~watchpoint()
{
}




WP* watchpoint::new_wp()
{
    WP *p = free_;
    if (free_ == NULL)
        assert(0);
    free_ = free_->next;
    free_->pro = NULL;

    p->next = head;
    if (head != NULL)
    {
        head->pro = p;
    }
    else
        head = p;
    p->pro = NULL;
    head = p;
    return p;
}

void watchpoint::free_wp(WP *wp)
{
    if (wp == NULL)
        assert(0);
    if (wp->pro != NULL && wp->next != NULL)
    {
        wp->pro->next = wp->next;
        wp->next->pro = wp->pro;
    }
    else if (wp->pro == NULL && wp->next != NULL)
    {
        head = wp->next;
    }
    else if (wp->pro != NULL && wp->next == NULL)
    {
        wp->pro->next = NULL;
    }
    else
    {
        head = NULL;
    }

    if (head == NULL)
    {
        free_ = wp;
        free_->pro = NULL;
        free_->next = NULL;
    }
    else
    {
        wp->next = free_;
        free_->pro = wp;
        free_ = wp;
    }
}

void watchpoint::theaddwatch(char *args)
{
    WP *w = new_wp();
    strcpy(w->exprStr, args);
    (w->exprStr)[strlen(args)] = '\0';
    printf("theaddwatch  %s\n", w->exprStr);
    bool success = 1;
    w->oldValue = Inexpr->ComputeExpr(args, &success);
    // if(!success)panic("expr errodsar!");
}
bool watchpoint::deletewatch(int n)
{
    WP *p = head;
    bool flag = 0;
    while (p)
    {
        if (p->NO == n)
        {
            free_wp(p);
            flag = true;
        }
        p = p->next;
    }
    return flag;
}
bool watchpoint::ifchange()
{
    WP *p = head;
    while (p)
    {
        bool success = 1;
        wchar_t newvalue = Inexpr->ComputeExpr(p->exprStr, &success);
        if (newvalue != p->oldValue)
        {
            printf("value is change \noldvalue : %x ==>  newvalue : %x\n", p->oldValue, newvalue);
            p->oldValue = newvalue;
            return true;
        }

        p = p->next;
    }
    return false;
}

void watchpoint::displaywatch()
{
    WP *p = head;
    printf("%-10s   %-10s   %s\n", "NUMBER", "WHAT", "VALUE");
    bool s;
    while (p)
    {
        Word_t number = Inexpr->ComputeExpr(p->exprStr, &s);
        printf("%-10d   %-10s   %x\n", p->NO, p->exprStr, number);
        p = p->next;
    }
}