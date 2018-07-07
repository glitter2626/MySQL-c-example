#include <stdio.h>

#include "mysql/mysql.h"



int main()

{

  const char *host = "localhost";

  const char *user = "root";

  const char *pass = "root";

  const char *db   = "test";

  MYSQL mysql;

  mysql_init(&mysql);



  if (!mysql_real_connect(&mysql, host, user, pass, db, 0, NULL, 0)) {

    printf("%s", mysql_error(&mysql));

  }

  else {

    printf("YES, Conected succeed!");

  }

  mysql_close(&mysql);

  return 0;

}
