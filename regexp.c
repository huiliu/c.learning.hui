#include <stdio.h>
#include <sys/types.h>
#include <regex.h>
#include <sqlite3.h>
#include <stdlib.h>
 
/* 取子串的函数 */
static char* substr(const char*str,unsigned start, unsigned end)
{
      unsigned n = end - start;
      static char stbuf[256];
      strncpy(stbuf, str + start, n);
      stbuf[n] = 0;
      return stbuf;
}
/* 主程序 */
int main(int argc, char** argv)
{
      char * pattern;
      int x, z, z1, lno = 0, cflags = 0;
      char ebuf[128], lbuf[256];
      regex_t reg, reg1;
      regmatch_t pm[10];
      const size_t nmatch = 10;

	  sqlite3 *db = NULL;
	  char *zErrMsg = 0;
	  int rc = 0;
	
	  rc = sqlite3_open("wubi.db",&db);
	  if( rc )
	  {
			  fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
			  sqlite3_close(db);
			  exit(1);
	  }

	  char *sql = "CREATE TABLE word (cn VARCHAR(3) NOT NULL, first VARCHAR(4) NOT NULL, sec VARCHAR(4), pri SMALLINT DEFAULT 0)";
	  sqlite3_exec( db, sql, 0, 0, &zErrMsg );
	  sql = "CREATE TABLE wordgroup (cn VARCHAR(12) NOT NULL, first VARCHAR(4) NOT NULL)";
	  sqlite3_exec( db, sql, 0, 0, &zErrMsg );


/* 编译正则表达式*/
      pattern = argv[1];	//获取正则表达式
      z = regcomp(&reg, pattern, REG_EXTENDED);	//如果编译成功返回0,其它返回说明有错误产生
	  z1 = regcomp(&reg1, "[a-y]*$", REG_EXTENDED);
      if (z != 0 && !z1)
      {
             regerror(z, &reg, ebuf, sizeof(ebuf));
             fprintf(stderr, "%s: pattern '%s' \n",ebuf, pattern);
             return 1;
      }
/* 逐行处理输入的数据 */
      while(fgets(lbuf, sizeof(lbuf), stdin))
      {
            ++lno;
//取得读取字符串的长度，并判断字符串结尾字符是否为回车符'\n'。如果是，将结尾字符改为0
            if ((z = strlen(lbuf)) > 0 && lbuf[z-1]== '\n')
                  lbuf[z - 1] = 0;
/* 对每一行应用正则表达式进行匹配 */
           z = regexec(&reg, lbuf, nmatch, pm, REG_NOTBOL);
           if (z == REG_NOMATCH) continue;	//如果没有匹配的，则继续下一次循环
           else if (z != 0)
           {
                  regerror(z, &reg, ebuf, sizeof(ebuf));
                  fprintf(stderr, "%s: regcom('%s')\n",ebuf, lbuf);
                  return 2;
           }
/* 输出处理结果 */
          for (x = 0; x < nmatch && pm[x].rm_so != -1; ++ x)
          {
                 if (!x) printf("%04d: %s\n", lno, lbuf);
                 printf(" $%d='%s'\n", x, substr(lbuf,pm[x].rm_so,pm[x].rm_eo));
          }
      }
/* 释放正则表达式 */
     regfree(&reg);
	 sqlite3_close(db);	//关闭数据库
     return 0;
}
