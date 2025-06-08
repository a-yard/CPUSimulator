#include "../../../Include/sdb.hpp"

char *sdb::rl_gets()
{
  static char *line_read = NULL;
  if (line_read)
  {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("wemu> ");

  if (line_read && *line_read)
  {
    add_history(line_read);
  }

  return line_read;
}

int sdb::cmd_c(char *args)
{
  this->CPUObj->cpu_exec(-1);
  return 0;
}

int sdb::cmd_q(char *args)
{
  // npc_state.state = NEMU_QUIT;
  return -1;
}

int sdb::cmd_si(char *args)
{
  int n = 1;
  if (args != NULL)
    n = atoi(args);
  this->CPUObj->cpu_exec(n);
  return 0;
}

int sdb::cmd_info(char *args)
{
  char *str = strtok(NULL, " ");
  if (strcmp(str, "r") == 0)
    this->CPUObj->ISAObj->DesplayReg();
    else if (strcmp(str, "csr") == 0)
    this->CPUObj->ISAObj->DesplayCSR();
  else if (strcmp(str, "w") == 0)
    this->watchpointObj->displaywatch();
  else
    printf("args error!\n");
  return 0;
}

int sdb::cmd_x(char *args)
{
  int N = atoi(strtok(NULL, " "));
  char *strexpr = strtok(NULL, " ");
  printf("strexpr %s N %d \n", strexpr, N);
  bool success;
  Word_t number = exprObj->ComputeExpr(strexpr, &success);
  printf("cmd_x %x\n", number);
  for (int i = 0; i < N * 4; i += 4)
  {
    printf("0x%-10x:   ", i + number);
    for (int j = 0; j < 4; j++)
    {
      printf("0x%-10.2x", BUSObj->BUSRead((i + j) + number, 1));
    }
    printf("\n");
  }
  return 0;
}

int sdb::cmd_w(char *args)
{
  this->watchpointObj->theaddwatch(args);
  return 0;
}
int sdb::cmd_d(char *args)
{
  this->watchpointObj->deletewatch(atoi(args));
  return 0;
}
int sdb::cmd_p(char *args)
{
  char *strexpr = strtok(NULL, " ");
  bool success = 0;
  printf("str %s\n", args);
  Word_t number = exprObj->ComputeExpr(args, &success);
  if (!success)
    assert(0);
  printf("%-10s %-10s\n", "Decimal", "hexadecimal");
  printf("%-10d 0x%-10x\n", number, number);
  return 0;
}

int sdb::cmd_help(char *args)
{
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL)
  {
    /* no argument given */
    for (i = 0; i < NR_CMD; i++)
    {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else
  {
    for (i = 0; i < NR_CMD; i++)
    {
      if (strcmp(arg, cmd_table[i].name) == 0)
      {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

void sdb::sdb_set_batch_mode()
{
  is_batch_mode = true;
}

void sdb::sdb_mainloop()
{
  if (is_batch_mode)
  {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL;)
  {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");

    if (cmd == NULL)
    {
      continue;
    }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end)
    {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i++)
    {
      if (strcmp(cmd, cmd_table[i].name) == 0)
      {
        if (this->SelectFun(i,args) < 0)
        {
          return;
        }
        break;
      }
    }

    if (i == NR_CMD)
    {
      printf("Unknown command '%s'\n", cmd);
    }
  }
}

sdb::sdb(BUS *InBUS,CPU * InCPU)
{


  this->exprObj = new expr();
  
  this->watchpointObj = new watchpoint(this->exprObj);
  
  CPUObj = InCPU;//new CPUExec(InNPC_State);
  this->BUSObj = InBUS;

  
  
  this->cmd_table[0] = {"help", "Display information about all supported commands"};
  this->cmd_table[1] = {"c", "Continue the execution of the program"};
  this->cmd_table[2] = {"q", "Exit NEMU"};

  this->cmd_table[3] = {"si", "Step into"};
  this->cmd_table[4] = {"info", "print reg"};
  this->cmd_table[5] = {"x", "Scan memory"};
  this->cmd_table[6] = {"w", "setting watch point"};
  this->cmd_table[7] = {"d", "delete watch point"};
  this->cmd_table[8] = {"p", "get expr value"};
}
int sdb::SelectFun(int n,char *args){
  switch (n)
  {
  case 0:return cmd_help(args);
  case 1:return cmd_c(args);
  case 2:return cmd_q(args);
  case 3:return cmd_si(args);
  case 4:return cmd_info(args);
  case 5:return cmd_x(args);
  case 6:return cmd_w(args);
  case 7:return cmd_d(args);
  case 8:return cmd_q(args);

  default:
    assert(0);
    break;
  }
}