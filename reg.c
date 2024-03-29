/*
 *  The program demostrate the regular pattern use C.
 *
 *  USAGE:
 *      ./reg   regex   < input_file
 *
 * Date: Tue Sep 25 00:16:18 CST 2012
 *
 *  TODO:
 *      improve the match pattern.
 */

#include <stdio.h>
#include <sys/types.h>
#include <regex.h>
#include <string.h>

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
      int x, z, lno = 0, cflags = 0;
      char ebuf[128], lbuf[256];
      regex_t reg;
      regmatch_t pm[10];
      const size_t nmatch = 10;

/* 编译正则表达式*/

      pattern = argv[1];    //获取正则表达式
      z = regcomp(&reg, pattern, cflags);   //如果编译成功返回0,其它返回说明有错误产生

      if (z != 0)
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
           z = regexec(&reg, lbuf, nmatch, pm, 0);
           if (z == REG_NOMATCH) continue;
           else if (z != 0)
           {
                  regerror(z, &reg, ebuf, sizeof(ebuf));
                  fprintf(stderr, "%s: regcom('%s')\n",ebuf, lbuf);

                  return 2;
           }

/* 输出处理结果 */
          for (x = 0; x < nmatch && pm[x].rm_so != -1; ++ x)
          {
//                 if (!x) printf("%04d: %s\n", lno, lbuf);
                 printf(" $%d='%s'\n", x, substr(lbuf,pm[x].rm_so,pm[x].rm_eo));
          }

      }

/* 释放正则表达式 */
     regfree(&reg);

     return 0;
}
