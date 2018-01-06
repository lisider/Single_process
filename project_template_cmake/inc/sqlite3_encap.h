#ifndef __SQLITE_ENCAP_H_
#define __SQLITE_ENCAP_H_

//write
extern int sqlite_wr(char * path,char *cmd);

//read
extern char * sqlite_rd_by_row_column(char * path,char *table,int row,int column,char * result ,int length);
extern char * sqlite_rd_total_row(char * path,char *table,char * result ,int length);
extern char * sqlite_rd_by_id(char * path,char *table,char *id ,int column,char * result ,int length);

extern int sqlite_rd_ifexist(char * path,char * table,char * filed ,char *value);

#endif
