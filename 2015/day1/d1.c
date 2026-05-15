#include <glib.h>
#include <stdio.h>
#include<glib.h>
#include<stddef.h>
#include<stdio.h>

int main(){
int leftP=0,rightP=0;
FILE* fd = fopen("p1.txt","r");
if(fd==NULL)
{
    perror("Can't open file");
    return 1;
}
int i=0;
int c;
while((c=fgetc(fd))!=EOF){
    if(c=='('){
        leftP++;
    }
    else leftP--;
   i++;
   if(leftP==-1){
       printf("Reached -1 at %d\n",i);
       break;
}
}
printf("%s %d %d\n","totals:",leftP,rightP);
/* Part 2 */
    GHashTable *hash_table = g_hash_table_new_full(
        g_str_hash, 
        g_str_equal, 
        (GDestroyNotify)g_free, 
        (GDestroyNotify)g_free
    );
    g_hash_table_insert(hash_table,g_strdup("Steve"),g_strdup("Slater"));
    
    g_hash_table_insert(hash_table,g_strdup("Stan"),g_strdup("Smith"));
    g_hash_table_insert(hash_table,g_strdup("Jeff"),g_strdup("Slater")); 

  char *lookfor="Stan";
  char *value=(char *)g_hash_table_lookup(hash_table,lookfor);
  if(value){
  printf("found it");
  }
    return 0;
} 
