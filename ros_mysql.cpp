#include<iostream>
#include<string>
#include<mysql/mysql.h>

using namespace std;

/******************************************************************************************************/

// $ g++ -o ros_mysql ros_mysql.cpp -lmysqlclient

class MyDB
{
    public:
    
        MyDB();
        ~MyDB();
        bool initDB(string host, string user, string pwd, string db_name); 
        bool exeSQL(string sql);   
        
    private:
    
        MYSQL *mysql;          
        MYSQL_RES *result;    
        MYSQL_ROW row;       
};

MyDB::MyDB()
{
    mysql=mysql_init(NULL);   
    
    if(mysql==NULL)
    {
        cout<<"Error:"<<mysql_error(mysql);
        exit(1);
    }
}

MyDB::~MyDB()
{
    if(mysql!=NULL)  
    {
        mysql_close(mysql);
    }
}


bool MyDB::initDB(string host, string user, string passwd, string db_name)
{
 
    // initialize, if failure return null 
    mysql = mysql_real_connect(mysql, host.c_str(), user.c_str(), passwd.c_str(), db_name.c_str(), 0, NULL, 0);  
    
    if(mysql == NULL)  
    {  
        cout << "Error: " << mysql_error(mysql);  
        exit(1);  
    }  
    return true;  
}

bool MyDB::exeSQL(string sql)
{
    // if mysql_query() success return 0
    if (mysql_query(mysql, sql.c_str()))
    {
        cout<<"Query Error: "<<mysql_error(mysql);
        return false;
    }
    else // query success
    {
        result = mysql_store_result(mysql);  // get result
        
        if (result)  
        {
           int  num_fields = mysql_num_fields(result);   // get columns
           int  num_rows = mysql_num_rows(result);       // get rows
           
           for(int i=0;i<num_rows;i++) 
            {
                // get next row data
                row = mysql_fetch_row(result);
                
                if(row<0) 
                    break;

                for(int j=0;j<num_fields;j++)  // output every columns
                {
                    /** TODO check database's data here **/
                    cout<<row[j]<<"\t";
                }
                cout<<endl;
            }

        }
        else  // result == NULL, means instruction is 'delete, insert or update...'
        {
            if(mysql_field_count(mysql) == 0)   
            {
                int num_rows = mysql_affected_rows(mysql);  // return affected rows
            }
            else // error
            {
                cout<<"Get result error: "<<mysql_error(mysql);
                return false;
            }
        }
    }

    return true;

}

/******************************************************************************************************/


int main()
{
    MyDB db; 
    
    //connect database
    db.initDB("localhost", "root", "root", "test");
    
    /*
    //add data
    db.exeSQL("INSERT accounts values('fengxin','123');");
    db.exeSQL("INSERT accounts values('axin','456');");
    */
    
    //read data
    db.exeSQL("SELECT * from user;");

    return 0;
}
