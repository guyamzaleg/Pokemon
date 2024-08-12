/*
 ============================================================================
 Name        : Pokedex.c
 Author      : Guy Amzaleg
 Version     :
 Copyright   :
 Description : main functionality and menu functions implements
 ============================================================================
 
 */

#include "Pokemon.h"

//==============================================================
//Function declarations of main functionality
//==============================================================

//input:
//			num_of_types,num_of_pokemons-int representing the number of types and pokemons in configuration file
//			path-char pointer :path to configuration file
//			Pokemons_list-a pointer to the list we will insert all pokemons in ,created from the configuration file 
//			Types_list-a pointer to the list we will insert all types in ,created from the configuration file 
//output: reads the file and insert the data from configuration file into the lists and return proccess status
status ReadFile(int num_of_types,int num_of_pokemons,char* path,Pokemon_list* PokemonList,Type_list* TypeList);

//input:
//output: prints all the menu and takes the input from the user-run until the number recieved is valid and return only valid integar between 1-9.
int ShowMenu();

//input: Poke_L-Pointer to a pokemons list
//output: Printing all the Pokemons in the list
status func1(Pokemon_list* Poke_L);

//input: Poke_L-Pointer to a Type list
//output: Printing all the Types in the list
status func2(Type_list* Type_L);

//input:Type_L-Pointer to a Type list
//output:Adding type recieved as an input inside the function to effective against me list of Type_L and return proccess status
status func3(Type_list* Type_L);

//input:Type_L-Pointer to a Type list
//output:Adding type recieved as an input inside the function to effective against others list of Type_L and return proccess status
status func4(Type_list* Type_L);

//input:Type_L Pointer to Type_list 
//output:Remove type recieved as an input inside the function from effective against me list of Type_L and return proccess status
status func5(Type_list* Type_L);


//input:Type_L Pointer to Type_list 
//output:Remove type recieved as an input inside the function from effective against others list of Type_L and return proccess status
status func6(Type_list* Type_L);

//input:Poke_L-a pointer to Pokemon_list
//output:Printing all the pokemons named as the input 
status func7(Pokemon_list* Poke_L);

//input:Poke_L-a pointer to Pokemon_list , type_L-a pointer to Type_list
//output:Printing all the pokemon inside Poke_L that their Type name is Type_L and return proccess status 
status func8(Pokemon_list* Poke_L,Type_list* Type_L);

int main(int argc,char* argv[])
{
	Type_list T_L;
	T_L=create_empty_type_list();

	Pokemon_list P_L;
	P_L=create_empty_pokemon_list();

	//Here the magic happens
	ReadFile(atoi(argv[1]),atoi(argv[2]),argv[3],&P_L,&T_L);
	status flag=failure;
	int choice=0;

	while(!flag )
	{
		choice=ShowMenu();
		switch (choice)
		{
			case 1:
				func1(&P_L);
				break;
	        case 2:
	        	func2(&T_L);
	            break;
	        case 3:
	        	func3(&T_L);
	            break;
	        case 4:
	            func4(&T_L);
	            break;
	        case 5:
	            func5(&T_L);
	            break;
	        case 6:
	        	func6(&T_L);
	            break;
	        case 7:
	        	func7(&P_L);
	            break;
	        case 8:
	        	func8(&P_L,&T_L);
	            break;
	        case 9:
	            flag=success;
	            break;
	    
		}
	}
	printf("All the memory cleaned and the program is safely closed.\n");
	free_type_list(&T_L);
	free_pokemon_list(&P_L);

}


//=======================================================================
//implement of menu functionality using pokemons functions
//=======================================================================

status ReadFile(int num_of_types,int num_of_pokemons,char* path,Pokemon_list* PokemonList,Type_list* TypeList)
{
	//printf("%d\n",num_of_types);
	//printf("%d\n",num_of_pokemons);

	char* current_name;
	char* ME_OTHER;
	char* Type1;
	char* current_name_of_type;
	Type* pcurrent_type;
	Type current_type;

	FILE* filePointer;
	int bufferLength = 300;
	char buffer[bufferLength]; /* max 300 is given*/
	filePointer = fopen(path, "r");

	fgets(buffer, bufferLength, filePointer);//First Line
	buffer[strcspn(buffer,"\n")-1] = '\0';	//find the line pass-and replace it with \0 for using string functions
	if(strcmp(buffer,"Types")==0 && num_of_types!=0) {
        //Next line is the Types
        fgets(buffer, bufferLength, filePointer);
        buffer[strcspn(buffer, "\n") -
               1] = '\0';    //find the line pass-and replace it with \0 for using string functions

        //first Type
        current_name = strtok(buffer, ",");

        //this loop is reading the types,creates them and insert them into TypeList->T_list
        for (int i = 0; i < num_of_types; i++) {
            current_type = create_new_type(current_name);
            pcurrent_type = &current_type;
            insert_type_to_type_list(TypeList, pcurrent_type);
            //print_type(&(TypeList->T_list[i]));
            current_name = strtok(NULL, ",");
            pcurrent_type = NULL;
        }

        //here the first line-insert Water and Ground to Fire->effective_against_me
        fgets(buffer, bufferLength, filePointer);

        //until the line is: "pokemons:" -there are effective against insert lines
        //this loop goes over all lines and insert the relevant types(Water and Ground) to the relevant sources(Fire) in the relevant lists(effective_against_me)
        while (strcmp(buffer, "Pokemons\r\n") != 0) {
            //Based on the effective against insert lines structure in Configuration File
            current_name_of_type = strtok(buffer, "\t -:,\r\n");//The source Type we want to insert into its lists
            strtok(NULL, "\t\t -:,\r\n"); //effective
            strtok(NULL, "\t\t -:,\r\n"); //against
            ME_OTHER = strtok(NULL, "\t\t -:,\r\n"); //me or other-the relevant list
            Type1 = strtok(NULL, "\t\t -:,\r\n");//First Type name to insert
            //Checking Validate
            if (strcmp(ME_OTHER, "me") != 0 && strcmp(ME_OTHER, "other") != 0) {
                return failure;
            }

            //reaching the source address inside the Type_list->T_list
            Type *current_source;
            for (int i = 0; i < num_of_types; i++) {
                if (strcmp(current_name_of_type, TypeList->T_list[i].Typename) == 0) {
                    current_source = &TypeList->T_list[i];
                }
            }
            enum e_bool inserted = false;
            int j = 0;
            //this loop update the source with the new Types in relevant lists(me/other) by using pointers to its address!!!!!
            while (j<num_of_types)
            {
                inserted=false;
                //======================================================================================================================================
                //======================================================================================================================================
                if (!Type1) {
                    break;
                }
                //======================================================================================================================================
                //======================================================================================================================================

                //insert into effective_against_me_list						=13 Because \r\n is 13-only way works for me handling this problem
                if (((strcmp(Type1, TypeList->T_list[j].Typename) == 0 ||
                      strcmp(Type1, TypeList->T_list[j].Typename) == 13)) && strcmp(ME_OTHER, "me") == 0) {
                    //if this is the end of the line-insert and exit the loop
                    if (strlen(Type1) > strlen(TypeList->T_list[j].Typename) + 1)        //The end of the line to enter
                    {
                        inserted=true;// /\r\n added
                        Type1[strcspn(Type1, "\r\n")] = '\0';
                        add_effective_against_me(current_source, &TypeList->T_list[j]);
                        break;
                    }
                    else
                    {
                        //else(if this is not the end of the line)-insert and continue to the next Type to insert
                        inserted=true;
                        add_effective_against_me(current_source, &TypeList->T_list[j]);
                        Type1 = strtok(NULL, "\t\t -:,");
                        j = 0;//go over all the types again-undependent in the locations or insert order
                    }
                }
//				//insert into effective_against_others_list						=13 Because \r\n is 13-only way works for me handling this problem
                if ((strcmp(Type1, TypeList->T_list[j].Typename) == 0 ||
                     strcmp(Type1, TypeList->T_list[j].Typename) == 13) && strcmp(ME_OTHER, "other") == 0)
                {
                    //if this is the end of the line-insert and exit the loop
                    if (strlen(Type1) > strlen(TypeList->T_list[j].Typename) + 1)        //The end of the list to enter
                    {                                                                                            // \r\n added
                        inserted=true;
                        Type1[strcspn(Type1, "\r\n")] = '\0';
                        add_effective_against_others(current_source, &TypeList->T_list[j]);
                        break;
                    } else {
                        //else(if this is not the end of the line)-insert and continue to the next Type to insert
                        inserted=true;
                        add_effective_against_others(current_source, &TypeList->T_list[j]);
                        Type1 = strtok(NULL, "\t\t -:,");
                        j = 0;//go over all the types again-undependent in the locations or insert order
                    }
                }
                if(inserted==false) {
                    j++;
                }
            }
            //Next Line to insert
            fgets(buffer, bufferLength, filePointer);
        }
    }

		//reaching here means buffer has "Pokemons:\r\n" now
		fgets(buffer, bufferLength, filePointer);
		
		//buffer has line contains first pokemon to insert now
		//run as many times as there are pokemon to read
		//this loop insert all the pokemons to the list recieved
		//based on the pokemons lines  structure
		for(int i=0;i<num_of_pokemons;i++)
		{
			char* name=strtok(buffer,",");
			char* species=strtok(NULL,",");
			float height=strtof(strtok(NULL,","),NULL);
			float weight=strtof(strtok(NULL,","),NULL);
			int attack=atoi(strtok(NULL,","));
			char* Poke_type=strtok(NULL,",");
			Poke_type[strcspn(Poke_type,"\r\n")] = '\0';
			Type* PPoke_type;

			//Reading its Type
			for (int i=0;i<num_of_types;i++)
			{
				//reaching the pokemon_type in the type list-and update the pokemons_type to point on
				if(strcmp(Poke_type,TypeList->T_list[i].Typename)==0)
				{
					PPoke_type=&TypeList->T_list[i];
				}
			}
			
			//creating poke Bio and Pokemon itself
			Bio B=create_new_bio(height,weight,attack);
			Pokemon P=create_new_pokemon(name,species,PPoke_type,B);

			//inserting the pokemon into the list saved in the main-by Adress!!!!!
			insert_pokemon_to_pokemon_list(PokemonList,&P);
			//next pokemon
			fgets(buffer, bufferLength, filePointer);
		}
	//close the file and free its allocation
	fclose(filePointer);
	
	return success;
}


int ShowMenu()
{
	bool flag=0;
	char choice[20]={"ABCDEFG"};
	while(choice[1]!='\0'||(choice[0]!='1' && choice[0]!='2'&&choice[0]!='3'&&choice[0]!='4'&&choice[0]!='5'&&choice[0]!='6'&&choice[0]!='7'&&choice[0]!='8'&&choice[0]!='9'))
	{
		if(flag)
		{
			printf("Please choose a valid number.\n");
		}
	printf("Please choose one of the following numbers:\n");
	printf("1 : Print all Pokemons\n");
	printf("2 : Print all Pokemons types\n");
	printf("3 : Add type to effective against me list\n");
	printf("4 : Add type to effective against others list\n");
	printf("5 : Remove type from effective against me list\n");
	printf("6 : Remove type from effective against others list\n");
	printf("7 : Print Pokemon by name\n");
	printf("8 : Print Pokemons by type\n");
	printf("9 : Exit\n");
	scanf("%s",choice);
	flag=1;
	}
	return atoi(choice);
}


//create empty type list
Type_list create_empty_type_list()
{
	Type_list new_type_list;
	new_type_list.T_size=0;
	new_type_list.T_list=(Type*)malloc(0);
	return new_type_list;
}

//Create empty Pokemon list
Pokemon_list create_empty_pokemon_list()
{
	Pokemon_list new_poke_list;
	new_poke_list.P_size=0;
	new_poke_list.P_list=(Pokemon*)malloc(0);
	return new_poke_list;
}

//Free the Type list-using free Type function
status free_type_list(Type_list* T_L)
{
	for(int i=0;i<T_L->T_size;i++)
	{
		free_type(&T_L->T_list[i]);
	}
	free(T_L->T_list);
	return success;
}

//Free the Pokemon list-using free Pokemon function
status free_pokemon_list(Pokemon_list* P_L)
{
	for (int i=0;i<P_L->P_size;i++)
	{
		free_pokemon(&P_L->P_list[i]);
	}
	free( P_L->P_list);
	return success;
}

//Print All Pokemons
status func1(Pokemon_list* Poke_L)
{
	//Prints all Pokemons
	for(int i=0;i<Poke_L->P_size;i++)
	{
		print_pokemon(&Poke_L->P_list[i]);
	}
	return success;
}

//Print all Pokemon Types
status func2(Type_list* Type_L)
{
	//Prints all Pokemon Types
	for(int i=0;i<Type_L->T_size;i++)
	{
		print_type(&Type_L->T_list[i]);
	}
	return success;
}

//Add type to effective against me list
status func3(Type_list* Type_L)
{
	//insert into effective against me list
	bool flagA=0;
	bool flagB=0;
	char buffer[20];
	char* Type_A;
	char* Type_B;
	int placeof_A=0;
	int placeof_B=0;
	printf("Please enter type name:\n");
	scanf("%s",buffer);
	Type_A=(char*)malloc(strlen(buffer));
	strcpy(Type_A,buffer);
	for(int i=0;i<Type_L->T_size;i++)
	{
		if(strcmp(Type_L->T_list[i].Typename,Type_A)==0)
		{
			placeof_A=i;
			flagA=1;
		}
	}
	if(flagA==0)
	{
		printf("Type name doesn't exist.\n");
		free(Type_A);
		return failure;
	}
	printf("Please enter type name to add to %s effective against me list:\n",Type_A);
	scanf("%s",buffer);
	Type_B=(char*)malloc(strlen(buffer));
	strcpy(Type_B,buffer);
	for (int i=0;i<Type_L->T_size;i++)
	{
		if(strcmp(Type_L->T_list[i].Typename,Type_B)==0)
		{
			placeof_B=i;
			flagB=1;
		}
	}
	if(flagB==0)
	{
		printf("Type name doesn't exist.\n");
		free(Type_A);
		free(Type_B);
		return failure;
	}
	for (int i=0;i<Type_L->T_list[placeof_A].size_of_effective_against_me;i++)
	{
		if(strcmp(Type_L->T_list[placeof_A].effective_against_me[i]->Typename,Type_B)==0)
		{
			printf("This type already exist in the list.\n");
			free(Type_A);
			free(Type_B);
			return failure;
		}
	}
	add_effective_against_me(&Type_L->T_list[placeof_A],&Type_L->T_list[placeof_B]);
	print_type(&Type_L->T_list[placeof_A]);
	free(Type_A);
	free(Type_B);
	return success;
}

//Add type to effective against others list
status func4(Type_list* Type_L)
{
	//insert into effective against others list
	bool flagA=0;
	bool flagB=0;
	char buffer[20];
	char* Type_A;
	char* Type_B;
	int placeof_A=0;
	int placeof_B=0;
	printf("Please enter type name:\n");
	scanf("%s",buffer);
	Type_A=(char*)malloc(strlen(buffer));
	strcpy(Type_A,buffer);
	for(int i=0;i<Type_L->T_size;i++)
	{
		if(strcmp(Type_L->T_list[i].Typename,Type_A)==0)
		{
			placeof_A=i;
			flagA=1;
		}
	}
	if(flagA==0)
	{
		printf("Type name doesn't exist.\n");
		free(Type_A);
		return failure;
	}
	printf("Please enter type name to add to %s effective against others list:\n",Type_A);
	scanf("%s",buffer);
	Type_B=(char*)malloc(strlen(buffer));
	strcpy(Type_B,buffer);
	for (int i=0;i<Type_L->T_size;i++)
	{
		if(strcmp(Type_L->T_list[i].Typename,Type_B)==0)
		{
			placeof_B=i;
			flagB=1;
		}
	}
	if(flagB==0)
	{
		printf("Type name doesn't exist.\n");
		free(Type_A);
		free(Type_B);
		return failure;
	}
	for (int i=0;i<Type_L->T_list[placeof_A].size_of_effective_against_others;i++)
	{
		if(strcmp(Type_L->T_list[placeof_A].effective_against_others[i]->Typename,Type_B)==0)
		{
			printf("This type already exist in the list.\n");
			free(Type_A);
			free(Type_B);
			return failure;
		}
	}
	add_effective_against_others(&Type_L->T_list[placeof_A],&Type_L->T_list[placeof_B]);
	print_type(&Type_L->T_list[placeof_A]);
	free(Type_A);
	free(Type_B);
	return success;
}

//remove type from effective against me list
status func5(Type_list* Type_L)
{
	//remove from effective against me list
		bool flagA=0;
		bool flagB=0;
		char buffer[20];
		char* Type_A;
		char* Type_B;
		int placeof_A=0;
		int placeof_B=0;
		printf("Please enter type name:\n");
		scanf("%s",buffer);
		Type_A=(char*)malloc(strlen(buffer));
		strcpy(Type_A,buffer);
		for(int i=0;i<Type_L->T_size;i++)
		{
			if(strcmp(Type_L->T_list[i].Typename,Type_A)==0)
			{
				placeof_A=i;
				flagA=1;
			}
		}
		if(flagA==0)
		{
			printf("Type name doesn't exist.\n");
			free(Type_A);
			return failure;
		}
		printf("Please enter type name to remove from %s effective against me list:\n",Type_A);
		scanf("%s",buffer);
		Type_B=(char*)malloc(strlen(buffer));
		strcpy(Type_B,buffer);
		for(int i=0;i<Type_L->T_size;i++)
				{
					if(strcmp(Type_L->T_list[i].Typename,Type_B)==0)
					{
						placeof_B=i;
						flagB=1;
					}
				}
				if(flagB==0)
				{
					printf("Type name doesn't exist in the list.\n");
					free(Type_A);
					free(Type_B);
					return failure;
				}
		for (int i=0;i<Type_L->T_list[placeof_A].size_of_effective_against_me;i++)
		{
			if(strcmp(Type_L->T_list[placeof_A].effective_against_me[i]->Typename,Type_B)==0)
			{
				remove_effective_against_me(&Type_L->T_list[placeof_A],&Type_L->T_list[placeof_B]);
				print_type(&Type_L->T_list[placeof_A]);
				free(Type_A);
				free(Type_B);
				return success;
			}
		}

		printf("Type name doesn't exist in the list.\n");
		free(Type_A);
		free(Type_B);
		return failure;


}

//remove type from effective against others list
status func6(Type_list* Type_L)
{
	//remove from effective against others list
	bool flagA=0;
			bool flagB=0;
			char buffer[20];
			char* Type_A;
			char* Type_B;
			int placeof_A=0;
			int placeof_B=0;
			printf("Please enter type name:\n");
			scanf("%s",buffer);
			Type_A=(char*)malloc(strlen(buffer));
			strcpy(Type_A,buffer);
			for(int i=0;i<Type_L->T_size;i++)
			{
				if(strcmp(Type_L->T_list[i].Typename,Type_A)==0)
				{
					placeof_A=i;
					flagA=1;
				}
			}
			if(flagA==0)
			{
				printf("Type name doesn't exist.\n");
				free(Type_A);
				return failure;
			}
			printf("Please enter type name to remove from %s effective against others list:\n",Type_A);
			scanf("%s",buffer);
			Type_B=(char*)malloc(strlen(buffer));
			strcpy(Type_B,buffer);
			for(int i=0;i<Type_L->T_size;i++)
					{
						if(strcmp(Type_L->T_list[i].Typename,Type_B)==0)
						{
							placeof_B=i;
							flagB=1;
						}
					}
					if(flagB==0)
					{
						printf("Type name doesn't exist in the list.\n");
						free(Type_A);
						free(Type_B);
						return failure;
					}
			for (int i=0;i<Type_L->T_list[placeof_A].size_of_effective_against_others;i++)
			{
				if(strcmp(Type_L->T_list[placeof_A].effective_against_others[i]->Typename,Type_B)==0)
				{
					remove_effective_against_others(&Type_L->T_list[placeof_A],&Type_L->T_list[placeof_B]);
					print_type(&Type_L->T_list[placeof_A]);
					free(Type_A);
					free(Type_B);
					return success;
				}
			}

			printf("Type name doesn't exist in the list.\n");
			free(Type_A);
			free(Type_B);
			return failure;
}

//Print pokemon by name
status func7(Pokemon_list* Poke_L)
{
	//prints pokemon by his name
	char buffer[20]={"ABCD"};
	char* name;
	printf("Please enter Pokemon name:\n");
	scanf("%s",buffer);
	name=(char*)malloc(strlen(buffer));
	strcpy(name,buffer);
	for (int i=0;i<Poke_L->P_size;i++)
	{
		if(strcmp(Poke_L->P_list[i].Poke_name,name)==0)
		{
			print_pokemon(&Poke_L->P_list[i]);
			free(name);
			return success;
		}
	}
	printf("The Pokemon doesn't exist.\n");
	free(name);
	return failure;
}

//Print pokemon by type
status func8(Pokemon_list* Poke_L,Type_list* Type_L)
{
	//print all pokemons from the type chosem
	char buffer[20];
	char* Type_name;
	status flag_name=0;
	int place_of_type=0;
	printf("Please enter type name:\n");
	scanf("%s",buffer);
	Type_name=(char*)malloc(strlen(buffer));
	strcpy(Type_name,buffer);
	for (int i=0;i<Type_L->T_size;i++)
	{
		if(strcmp(Type_L->T_list[i].Typename,Type_name)==0)
		{
			place_of_type=i;
			flag_name=1;
		}
	}
	if(!flag_name)
	{
		printf("Type name doesn't exist.\n");
		free(Type_name);
		return failure;
	}
	printf("There are %d Pokemons with this type:\n",Type_L->T_list[place_of_type].how_many);
	for (int i=0;i<Poke_L->P_size;i++)
	{
		if(strcmp(Poke_L->P_list[i].Poke_type->Typename,Type_name)==0)
		{
			print_pokemon(&Poke_L->P_list[i]);
		}
	}
	free(Type_name);
	return success;
}
