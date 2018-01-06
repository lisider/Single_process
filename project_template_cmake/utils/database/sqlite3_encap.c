/*************************************************************************
    > File Name: sqlite.c
    > Author: Sues
    > Mail: sumory.kaka@foxmail.com 
    > Created Time: Thu 23 Feb 2017 05:30:37 PM CST
 ************************************************************************/

#include <sqlite3.h>
#include <pthread.h>
#include <string.h>

pthread_rwlock_t lock; 

//write


int sqlite_write_core(char *path,char *cmd){

	pthread_rwlock_wrlock(&lock);
	sqlite3 *dbp;
	char ** re_val;
	char *err;


	if(SQLITE_OK != sqlite3_open(path,&dbp)){
		puts("open file error!");
		return -1;
	}


	if(SQLITE_OK != sqlite3_get_table(dbp,
				cmd,&re_val,NULL,NULL,&err)){
		puts(err);
	}


	sqlite3_free_table(re_val);
	sqlite3_close(dbp);
	pthread_rwlock_unlock(&lock);
	return 0;
}

int sqlite_wr_insert_record(char * path,char *cmd){
	return sqlite_write_core(path,cmd);
}


int sqlite_wr_del_record(char * path,char *cmd){
	return sqlite_write_core(path,cmd);
}


//---------------------------------------------------------------------------------------------

//read


//path db 的全路径
//table  哪个表
//cmd 执行的命令
//row 检索的哪一行
//column 检索的哪一列
//result 检索的结果存放位置
//length 检索的结果存放位置所占内存的大小

char *sqlite_read_core(char *path,char *table,char *cmd,int row,int column,char *result,int length){

	pthread_rwlock_rdlock(&lock);
	sqlite3 *dbp;
	char ** re_val;
	char *err;
	int i,j;
	int row_ = 0,column_ = 0;

	if(SQLITE_OK != sqlite3_open(path,&dbp)){
		puts("open file error!");
		return (char *)-1;
	}

	if(SQLITE_OK != sqlite3_get_table(dbp,
				cmd,&re_val,&row_,&column_,&err)){
		puts(err);
	}

	if(row_ >= 1){
		bzero(result,length);
		strcpy(result,re_val[row*column_ + column]);
	}
	sqlite3_free_table(re_val);
	sqlite3_close(dbp);
	pthread_rwlock_unlock(&lock);
	return result;
}


int sqlite_rd_ifexist(char * path,char * table,char * filed ,char *value){

	char result[64] = {0};

	char buf[64] = {0};
	strcat(buf,"select * from ");
	strcat(buf,table);
	strcat(buf," where ");
	strcat(buf,filed);
	strcat(buf," = ");
	strcat(buf,value);
	strcat(buf,";");


	sqlite_read_core(path,table,buf,1,0,result,sizeof(result));
	if(result[0] == 0){
		return 0;
	}else
		return 1;

}

char * sqlite_rd_by_row_column(char * path,char *table,int row,int column,char * result ,int length){

	char buf[64];
	bzero(buf,sizeof(buf));
	strcat(buf,"select * from ");
	strcat(buf,table);
	strcat(buf,";");

	sqlite_read_core(path,table,buf,row,column,result,length);

}

char * sqlite_rd_total_row(char * path,char *table,char * result ,int length){


	char buf[64];
	bzero(buf,sizeof(buf));
	strcat(buf,"select count (*) from ");
	strcat(buf,table);
	strcat(buf,";");

	return sqlite_read_core(path,table,buf,1,0,result,length);

}

//这个是 特殊的函数
//依靠 stu_ 的 id 
//查找 score_ 的 row

char * sqlite_rd_by_id(char * path,char *table,char *id ,int column,char * result ,int length){

	char buf[64];
	bzero(buf,sizeof(buf));
	strcat(buf,"select * from ");
	strcat(buf,table);
	strcat(buf," where id = ");
	strcat(buf,id);
	strcat(buf,";");
	//puts(buf);
	return sqlite_read_core(path,table,buf,1,column,result,length);
}

