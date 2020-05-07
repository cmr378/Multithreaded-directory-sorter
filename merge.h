#ifndef MERGE_H
#define MERGE_H

void merging( Movie *inp, int low, int mid, int high, char *colName ) {

   int mergeSize = high - low + 1;

   Movie *temp = (Movie *)malloc( mergeSize * sizeof( Movie ) );
   //char title[100];

	int i = 0;
	int l1 = low;
	int r1 = mid + 1;

   while (l1 <= mid && r1 <= high) {


	if ( strcmp( colName, "color" ) == 0 ) {
		if ( strcmp(inp[l1].color,inp[r1].color ) < 0 ) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "director_name" ) == 0 ) {
		if ( strcmp(inp[l1].director_name,inp[r1].director_name ) < 0) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "num_critic_for_reviews" ) == 0 ) {
		if ( atof(inp[l1].num_critic_for_reviews) < atof(inp[r1].num_critic_for_reviews )) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "duration" ) == 0 ) {
		if ( atof(inp[l1].duration) < atof(inp[r1].duration)) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "director_facebook_likes" ) == 0 ) {
		if ( atof(inp[l1].director_facebook_likes) < atof(inp[r1].director_facebook_likes) ) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "actor_3_facebook_likes" ) == 0 ) {
		if ( atof(inp[l1].actor_3_facebook_likes) < atof(inp[r1].actor_3_facebook_likes) ) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "actor_2_name" ) == 0 ) {
		if ( strcmp(inp[l1].actor_2_name, inp[r1].actor_2_name) < 0 ) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "actor_1_facebook_likes" ) == 0 ) {
		if ( atof(inp[l1].actor_1_facebook_likes) < atof(inp[r1].actor_1_facebook_likes )) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "gross" ) == 0 ) {
		if ( atof(inp[l1].gross) < atof(inp[r1].gross)) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "genres" ) == 0 ) {
		if ( strcmp(inp[l1].genres, inp[r1].genres) < 0 ) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "actor_1_name" ) == 0 ) {
		if ( strcmp(inp[l1].actor_1_name, inp[r1].actor_1_name ) < 0) {
			temp[i++] = inp[l1++];
		} 	else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "movie_title" ) == 0 ) {

		int n = 0;
		if (inp[l1].movie_title[0] == '"' && inp[r1].movie_title[0] != '"') {
			while (n < strlen(inp[l1].movie_title)-1) {
				if (inp[l1].movie_title[n+1] == '"') {
					inp[l1].movie_title[n] = '\0';
					break;
				}
				inp[l1].movie_title[n] = inp[l1].movie_title[n+1];
				n++;
			}
		} else if (inp[l1].movie_title[0] != '"' && inp[r1].movie_title[0] == '"') {
			while (n < strlen(inp[r1].movie_title)-1) {
				if (inp[r1].movie_title[n+1] == '"') {
					inp[r1].movie_title[n] = '\0';
					break;
				}
				inp[r1].movie_title[n] = inp[r1].movie_title[n+1];
				n++;
			}
		}

		if ( strcmp(inp[l1].movie_title , inp[r1].movie_title) < 0 ) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "num_voted_users" ) == 0 ) {
		if ( atof(inp[l1].num_voted_users) < atof(inp[r1].num_voted_users)) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "cast_total_facebook_likes" ) == 0 ) {
		if ( atof(inp[l1].cast_total_facebook_likes) < atof(inp[r1].cast_total_facebook_likes)) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "actor_3_name" ) == 0 ) {
		if ( strcmp(inp[l1].actor_3_name, inp[r1].actor_3_name) < 0 ) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "facenumber_in_poster" ) == 0 ) {
		if ( atof(inp[l1].facenumber_in_poster) < atof(inp[r1].facenumber_in_poster) ) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "plot_keywords" ) == 0 ) {
		if ( strcmp(inp[l1].plot_keywords, inp[r1].plot_keywords) <0 ) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "movie_imdb_link" ) == 0 ) {
		if ( strcmp(inp[l1].movie_imdb_link , inp[r1].movie_imdb_link) < 0 ) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "num_user_for_reviews" ) == 0 ) {
		if ( atof(inp[l1].num_user_for_reviews) < atof(inp[r1].num_user_for_reviews)) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "language" ) == 0 ) {
		if ( strcmp(inp[l1].language ,inp[r1].language) < 0 ) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "country" ) == 0 ) {
		if ( strcmp(inp[l1].country , inp[r1].country) < 0 ) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "content_rating" ) == 0 ) {
		if ( strcmp(inp[l1].content_rating, inp[r1].content_rating) < 0 ) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "budget" ) == 0 ) {
		if ( atof(inp[l1].budget) < atof(inp[r1].budget)) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "title_year" ) == 0 ) {
		if ( atof(inp[l1].title_year) < atof(inp[r1].title_year) ) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "actor_2_facebook_likes" ) == 0 ) {
		if ( atof(inp[l1].actor_2_facebook_likes) < atof(inp[r1].actor_2_facebook_likes)) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "imdb_score" ) == 0 ) {
		if ( atof( inp[l1].imdb_score) < atof(inp[r1].imdb_score) ) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "aspect_ratio" ) == 0 ) {
		if ( atof(inp[l1].aspect_ratio) < atof(inp[r1].aspect_ratio )) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	} else if ( strcmp( colName, "movie_facebook_likes" ) == 0 ) {
		if ( atof(inp[l1].movie_facebook_likes) < atof(inp[r1].movie_facebook_likes)) {
			temp[i++] = inp[l1++];
		} else {
			temp[i++] = inp[r1++];
		}
	}

   }

   while( l1 <= mid ) {
      temp[i++] = inp[l1++];
      	}
   while( r1 <= high )  {
      temp[i++] = inp[r1++];
      }
   for( i = 0; i < mergeSize; ++i) {
      inp[i + low] = temp[i];
      }
   free( temp );

}

void sort( Movie *inp, int low, int high, char *colName) {

   if( low < high ) {

      int mid = ( low + high ) / 2;

      sort( inp, low, mid, colName );
      sort( inp, mid+1, high, colName );

      merging( inp, low, mid, high, colName );

   } else {
   	return;
   }
}

#endif
