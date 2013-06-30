#include <string.h>
#include <stdio.h>
int
main (void)
{
	  char buffer[256];
	    char *to = buffer, *sql;
		  to = stpcpy (to, "foo");
		    to = stpcpy (to, "bar");
			  puts (buffer);
	sql = buffer;
	sql = stpcpy(sql,"INSERT INTO word VALUES (\'");
    sql = stpcpy( sql," word");
    sql = stpcpy( sql, "\', \'");
    sql = stpcpy( sql, "a");
    sql = stpcpy( sql, "\', \'");
    sql = stpcpy( sql,"b");
    sql = stpcpy( sql, "\', 0)");
    printf("插入数据：%s\n", buffer);

	return 0;
}

