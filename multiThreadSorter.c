#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "multiThreadSorter.h"
#include "merge.h"

typedef struct csvAtt {

  int numRows;
  Movie * currCsv;

}csv;

char dirs[255][108];
int output;
int numDirs;
int numFiles;
int threadCount;
char targetCol[150];
char outputDir[150];
char targetDir[150];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
Movie * mainArray;
int mainARows;


char* concat(const char *s1, const char *s2) //function from stack overflow (david heffernan)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator

    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void getDirs(char * dir){
    //printf("numFiles IS %d\n",numFiles + 1);
    strcpy(dirs[numFiles],dir);
    printf("Just copied: %s\n",dir);
    //printf("REC DIRECTORY: %s\n",dirs[numFiles]);
}

char * getFileName(char * str1, char * str2){
  char * finalName = (char*)malloc(100 * sizeof(char));
  char * secondPart = (char*)malloc(50 * sizeof(char));
  char * first = "<";
  char * last = ">";
  char * ext = ".csv";

  //makes <colName>
  secondPart = concat(first,str2);
  secondPart = concat(secondPart,last);

  //final string
  finalName = concat(str1,secondPart);
  finalName = concat(finalName,ext);

  return finalName;
}

char * correctPath(){

	int length = 0;
	int i = 0;

  printf("Numdirs is: %d\n",numDirs);

	if(numDirs == 0 || output < 3){
		return "currentPath";
	}

	for(i = 0; i < numDirs;i++){
		printf("DIR: %s\n",dirs[i]);
		length += strlen(dirs[i]);
	}

	 length += 1; // for extra chars
	printf("Length is: %d\n",length);
	char newPath[length];

	i = 0;
	int k = 0;
	int j = 0;

	int totalPartitions = numDirs - 1;
	int numPartitions = 0;
	int size = 0;
	int totalSize = 0;

	for(i = 0; i < numDirs; i++){

		size = strlen(dirs[i]);
		totalSize += size;

		if(totalSize == length){
			break;
		}
		j = 0;

		while(j <= size){

			if( j != size){
				newPath[k] = dirs[i][j];
			}

			else if(j == size && numPartitions < totalPartitions){
				newPath[k] = '/';
				numPartitions++;
			}

			j++;
			k++;
		}
	}

	char * finalPath = (char*)malloc(length * sizeof(char));

	for(i = 0; i < length; i++){
		finalPath[i] = newPath[i];
	}

	printf("newPath is %s\n",finalPath);
	return finalPath;
}

void concatFiles(Movie * mainArray){

  char * check = correctPath();
  printf("CORRECT PTAH IS: %s\n",check);

  if(strcmp(check,"currentPath") == 0){
    int i = 0;
    char * finalFile = (char*)malloc(50 * sizeof(char));
    finalFile = getFileName("AllFiles-sorted-",targetCol);

    FILE * output = fopen(finalFile,"w");

    fprintf(
      output,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
      "color","direcctor_name","num_critic_for_reviews","duration",
      "director_facebook_likes","actor_3_facebook_likes","actor_2_name",
      "actor_1_facebook_likes","gross","genres","actor_1_name",
      "movie_title","num_voted_users","cast_total_facebook_likes",
      "actor_3_name","facenumber_in_poster","plot_keywords",
      "movie_imdb_link","num_user_for_reviews","language","country",
      "content_rating","budget","title_year","actor_2_facebook_likes",
      "imdb_score","aspect_ratio","movie_facebook_likes"
    );

    for(i = 0; i < mainARows;i++){
      fprintf(
        output,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
        mainArray[i].color,mainArray[i].director_name,
        mainArray[i].num_critic_for_reviews,mainArray[i].duration,
        mainArray[i].director_facebook_likes,mainArray[i].actor_3_facebook_likes,
        mainArray[i].actor_2_name,mainArray[i].actor_1_facebook_likes,
        mainArray[i].gross,mainArray[i].genres,
        mainArray[i].actor_1_name,mainArray[i].movie_title,
        mainArray[i].num_voted_users,mainArray[i].cast_total_facebook_likes,
        mainArray[i].actor_3_name,mainArray[i].facenumber_in_poster,
        mainArray[i].plot_keywords,mainArray[i].movie_imdb_link,
        mainArray[i].num_user_for_reviews,mainArray[i].language,
        mainArray[i].country,mainArray[i].content_rating,
        mainArray[i].budget,mainArray[i].title_year,
        mainArray[i].actor_2_facebook_likes,mainArray[i].imdb_score,
        mainArray[i].aspect_ratio,mainArray[i].movie_facebook_likes
      );
    }

  }

  else {
    int i = 0;
    char * finalFile = (char*)malloc(150 * sizeof(char));
    finalFile = getFileName("AllFiles-sorted-",targetCol);
    printf("Should be this: %s\n",finalFile);
    char * correction = concat(check,"/");
    char * finalPath = concat(correction,finalFile);

    printf("Correct path: %s\n",finalPath);

    FILE * output = fopen(finalPath,"w");

    if(output == NULL){
      printf("error creating file\n");
      exit(0);
    }

    fprintf(
      output,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
      "color","direcctor_name","num_critic_for_reviews","duration",
      "director_facebook_likes","actor_3_facebook_likes","actor_2_name",
      "actor_1_facebook_likes","gross","genres","actor_1_name",
      "movie_title","num_voted_users","cast_total_facebook_likes",
      "actor_3_name","facenumber_in_poster","plot_keywords",
      "movie_imdb_link","num_user_for_reviews","language","country",
      "content_rating","budget","title_year","actor_2_facebook_likes",
      "imdb_score","aspect_ratio","movie_facebook_likes"
    );

    for(i = 0; i < mainARows; i++){
      fprintf(
        output,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
        mainArray[i].color,mainArray[i].director_name,
        mainArray[i].num_critic_for_reviews,mainArray[i].duration,
        mainArray[i].director_facebook_likes,mainArray[i].actor_3_facebook_likes,
        mainArray[i].actor_2_name,mainArray[i].actor_1_facebook_likes,
        mainArray[i].gross,mainArray[i].genres,
        mainArray[i].actor_1_name,mainArray[i].movie_title,
        mainArray[i].num_voted_users,mainArray[i].cast_total_facebook_likes,
        mainArray[i].actor_3_name,mainArray[i].facenumber_in_poster,
        mainArray[i].plot_keywords,mainArray[i].movie_imdb_link,
        mainArray[i].num_user_for_reviews,mainArray[i].language,
        mainArray[i].country,mainArray[i].content_rating,
        mainArray[i].budget,mainArray[i].title_year,
        mainArray[i].actor_2_facebook_likes,mainArray[i].imdb_score,
        mainArray[i].aspect_ratio,mainArray[i].movie_facebook_likes
      );
    }
  }
}



int numRows( FILE *fp )
{
	int totalRows = 0;
	int buffer = 2040;
	char line[buffer];

	while( fgets( line, buffer, fp ) != NULL )
	{
		totalRows++;
	}
	return totalRows;
}



char * tokenizer (char * str, char const * delims)
{
  static char  * src = NULL;
  char  *  p,  * ret = 0;

  if (str != NULL)
    src = str;

  if (src == NULL)
    return NULL;

  if ((p = strpbrk (src, delims)) != NULL) {
    *p  = 0;
    ret = src;
    src = ++p;

  } else if (src) { //changed from *src -> src
    ret = src;
    src = NULL;
  }

  return ret;
}



csv csvReader( char * path ){
    //Create and read from file
    FILE *fp;
    fp = fopen( path, "r" );

    //Make sure CSV file is there
    if ( !fp ) {
            perror( "No CSV file found." );
    }

    csv currentFile;
    int totalRows = numRows(fp) - 1;

    rewind(fp); // counted total columns for better memory allocation had to rewind

    Movie * movieTab2 = (Movie *)malloc(totalRows * sizeof(Movie));

    int bufferSize = 4080;
    char buffer[bufferSize];

    int colCount = 0;
    int rowCount = 0;

    char * token = (char *)malloc( 1000 * sizeof( char ) );
    char *subToken = (char *)malloc( 1000 * sizeof( char ) );

    fgets( buffer, sizeof( buffer ), fp ); //getting rid of column names
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {

    colCount = 1;

    token = tokenizer(buffer, ",");

    while (token) {
      strcpy(subToken, token); // this is where the segfault occurred/Increased the size of struct attributes

      /*while (subToken[strlen(subToken)-1] == '"') {
            token = tokenizer(NULL, ",");
            strcat(subToken, token);
          }*/

        strcpy(token, subToken);
        switch (colCount) {
                case 1:
                    strcpy(movieTab2[rowCount].color, token);
                    break;
                case 2:
                    strcpy(movieTab2[rowCount].director_name , token);
                    break;
                case 3:
                    strcpy(movieTab2[rowCount].num_critic_for_reviews , token);
                    break;
                case 4:
                    strcpy(movieTab2[rowCount].duration , token);
                    break;
                case 5:
                    strcpy(movieTab2[rowCount].director_facebook_likes , token);
                    break;
                case 6:
                    strcpy(movieTab2[rowCount].actor_3_facebook_likes , token);
                    break;
                case 7:
                    strcpy(movieTab2[rowCount].actor_2_name , token);
                    break;
                case 8:
                    strcpy(movieTab2[rowCount].actor_1_facebook_likes , token);
                    break;
                case 9:
                    strcpy(movieTab2[rowCount].gross , token);
                    break;
                case 10:
                    strcpy(movieTab2[rowCount].genres , token);
                    break;
                case 11:
                    strcpy(movieTab2[rowCount].actor_1_name , token);
                    break;
                case 12:
                    strcpy(movieTab2[rowCount].movie_title , token);
                    break;
                case 13:
                    strcpy(movieTab2[rowCount].num_voted_users , token);
                    break;
                case 14:
                    strcpy(movieTab2[rowCount].cast_total_facebook_likes , token);
                    break;
                case 15:
                    strcpy(movieTab2[rowCount].actor_3_name , token);
                    break;
                case 16:
                    strcpy(movieTab2[rowCount].facenumber_in_poster , token);
                    break;
                case 17:
                    strcpy(movieTab2[rowCount].plot_keywords , token);
                    break;
                case 18:
                    strcpy(movieTab2[rowCount].movie_imdb_link , token);
                    break;
                case 19:
                    strcpy(movieTab2[rowCount].num_user_for_reviews , token);
                    break;
                case 20:
                    strcpy(movieTab2[rowCount].language , token);
                    break;
                case 21:
                    strcpy(movieTab2[rowCount].country , token);
                    break;
                case 22:
                    strcpy(movieTab2[rowCount].content_rating , token);
                    break;
                case 23:
                    strcpy(movieTab2[rowCount].budget , token);
                    break;
                case 24:
                    strcpy(movieTab2[rowCount].title_year , token);
                    break;
                case 25:
                    strcpy(movieTab2[rowCount].actor_2_facebook_likes , token);
                    break;
                case 26:
                    strcpy(movieTab2[rowCount].imdb_score , token);
                    break;
                case 27:
                    strcpy(movieTab2[rowCount].aspect_ratio , token);
                    break;
                case 28:
                    strcpy(movieTab2[rowCount].movie_facebook_likes, token);
                    break;
         }
        // printf( "%d\n", colCount );
         token = tokenizer(NULL, ",");
         ++colCount;
         //printf( "token: %s\n", token );
        }
        ++rowCount;
    //printf( "his m%d%s\n", rowCount,token );
    } //current error here edit2
        // printf( "his\n" );

    //printf( "asdf %s\n", movieTab2[200].director_name );
    currentFile.currCsv = movieTab2;
    currentFile.numRows = totalRows;
    return currentFile;
}



void * sortMech( void * path ){

  printf("Current file in sortMech: %s\n",path);

  csv currentFile;

  pthread_mutex_lock(&mutex);
    currentFile = csvReader( path ); //set back to temporary array
  pthread_mutex_unlock(&mutex);

  printf( "testing the table: %s with %d rows\n", currentFile.currCsv[5000].actor_3_name, currentFile.numRows);

  //sort(currentFile.currCsv,0,currentFile.numRows-1,targetCol);

  printf("Sorted %s\n",path);

  int i;
  int iPa;
  int oldmainARows = mainARows;
  for( i = 0; i < currentFile.numRows; i++ ) //may need mutex. CURRENTTHING!!
  {
      //printf( "doing %s to %d\n", currentFile.currCsv[i].movie_title, ( i + oldmainARows ) );
      iPa = i + oldmainARows;
      mainArray[iPa] = currentFile.currCsv[i];
      mainARows++;
  }
  for( i = 0; i < mainARows; i++ )
  {
  	//printf( "Index: %d. Movie: %s.\n", i, mainArray[i].color );
  }
  return NULL;
}



void * fileSearch(void * dir){

  //directory structure
  struct dirent *de;
  DIR * dr = opendir(dir);

  if(dr == NULL){
    printf("Could not open directory\n");
    return 0;
  }

  while((de = readdir(dr)) != NULL){

    //directory structure threads

    if(strcmp(de->d_name,"..") == 0 || strcmp(de->d_name,".") == 0)
      continue;

    else if(de->d_type == DT_DIR) {

        printf("\nDIRECTORY: [%s]\n",de->d_name);
        getDirs(de->d_name);
        numDirs++;

        char *slash = concat( dir, "/" );
        slash = concat( slash, de->d_name );

      // New thread for new directory, mutexe needed

      //directory structure thread
      pthread_t tid;
      pthread_attr_t attr;
      pthread_attr_init(&attr);

      pthread_create(&tid,&attr,fileSearch,slash);

      printf("%d\n",getpid());
    }

    else {

      printf("%s\n", de->d_name);

      int len = strlen( de->d_name );
      const char *exten = &de->d_name[len-4];

      if (strcmp(exten, ".csv" ) == 0 ){

        printf( "Doing the sort on %s\n", de->d_name );
        numFiles++;
        char *slash = concat( dir, "/" );
        slash = concat( slash, de->d_name );

        // sorting thread here !

         pthread_t tid;
           pthread_attr_t attr;
           pthread_attr_init(&attr);

           pthread_create(&tid,&attr,sortMech,slash);
         pthread_join(tid, NULL);
      //returning values??
      }

    }
  }
  closedir(dr);
  return NULL;
}


void * searchHelp(char * dir){
  //creating the main thread
  //thread id
  pthread_t tid;

  //thread attributes
  pthread_attr_t attr;

  pthread_attr_init(&attr);

  pthread_create(&tid,&attr,fileSearch,dir);

  pthread_join(tid,NULL);
  //put ultimate merging here probably.. or merge within each pthread but will require mutexes
  /*
  1) Start linked list loop
  2) Loop through main array from current end val -> current end val + curNode.rowCount
  3) Set main array row currentEndVal+i = curNode.csv[i]
  4) End loop
  5) Sort again..??? although whats the point of threading then besides minimal efficiency
  6) Export as new csv
  */
  return NULL;
}

int checkFlags(int argc, char * argv[], char * flags){

   if(argc == 3){
    if(strcmp(flags,"-c") == 0){
      output = 1;
      strcpy(targetCol,argv[2]);
      strcpy(targetDir,".");
      return output;
    }

    else {
      printf("No matching flags\n");
      exit(0);
    }
  }

  else if(argc == 5){

    if(strcmp(flags,"-c-d") == 0){
      strcpy(targetCol,argv[2]);
      strcpy(targetDir,argv[4]);
      output = 2;
      return output;
    }

    else if(strcmp(flags,"-d-c") == 0){
      strcpy(targetCol,argv[4]);
      strcpy(targetDir,argv[2]);
      output = 2;
      return output;
    }

    else if(strcmp(flags,"-c-o") == 0){
      strcpy(targetCol,argv[2]);
      strcpy(outputDir,argv[4]);
      output = 4;
      return output;
    }

    else if(strcmp(flags,"-o-c") == 0){
      strcpy(targetCol,argv[4]);
      strcpy(outputDir,argv[2]);
      output = 4;
      return output;
    }

    else {
      printf("No matching flags\n");
      exit(0);
    }
  }

  else if(argc == 7){

    if(strcmp(flags,"-c-o-d") == 0){
      strcpy(targetCol,argv[2]);
      strcpy(outputDir,argv[5]);
      strcpy(targetDir,argv[6]);
      output = 3;
      return output;
    }

      else if( strcmp(flags,"-d-o-c") == 0){
        strcpy(targetDir,argv[2]);
        strcpy(outputDir,argv[4]);
        strcpy(targetCol,argv[6]);
        output = 3;
        return output;
      }

    else if(strcmp(flags,"-o-c-d") == 0){
      strcpy(outputDir,argv[2]);
      strcpy(targetCol,argv[4]);
      strcpy(targetDir,argv[6]);
      output = 3;
      return output;
    }

    else if(strcmp(flags,"-d-c-o") == 0){
      strcpy(targetDir,argv[2]);
      strcpy(targetCol,argv[4]);
      strcpy(outputDir,argv[6]);
      output = 3;
      return output;
    }

    else if(strcmp(flags,"-c-d-o") == 0){
      strcpy(targetCol,argv[2]);
      strcpy(targetDir,argv[4]);
      strcpy(outputDir,argv[6]);
      output = 3;
      return output;
    }

    else if(strcmp(flags,"-o-d-c") == 0){
      strcpy(outputDir,argv[2]);
      strcpy(targetDir,argv[4]);
      strcpy(targetCol,argv[6]);
      output = 3;
      return output;
    }

    else {
      printf("No matching flags\n");
      exit(0);
    }
  }
  //printf("output is : %d\n",output);
  return output;
}

char * createFlags(int argc, char * argv[]){
  int i = 0;

  char * newString = (char*)malloc(6 * sizeof(char));

  while(i < argc){

    if(i == 1){
      strcpy(newString,argv[1]);
    }

    else if(i == 3){
      strcat(newString,argv[3]);
    }

    else if(i == 5){
      strcat(newString,argv[5]);
    }
    i++;
  }

  //printf("NEW %s\n",newString);

  return newString;

}

int main(int argc, char * argv[]){
  mainArray = (Movie *)malloc(99999 * sizeof(Movie));
  mainARows = 0;

  if(argc < 3){
    printf("Not enough arguments\n");
    return 0;
  }
  else {
    char * flags = createFlags(argc,argv);
    output = checkFlags(argc,argv,flags);
    //printf("output is: %d\n",output);
    //printf("Target Column: %s \nTarget directory: %s \nOutput directory: %s \n",targetCol,targetDir,outputDir);

    if(output == 1){
      searchHelp(".");
    }

    else if(output == 2){
      searchHelp(targetDir);
    }

    else if(output == 3){
      searchHelp(targetDir);
    }

    else if(output == 4){
      searchHelp(".");
    }
  }
  
  concatFiles(mainArray);

  return 0;
}
