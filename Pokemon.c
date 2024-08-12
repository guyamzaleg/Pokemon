/*
 ============================================================================
 Name        : Pokemon.c
 Author      : Guy Amzaleg
 Version     :
 Copyright   : 
 Description :	includes All implements of all functions related to Pokemons
 ============================================================================
*/

#include "Pokemon.h"

//implement of Pokemon functions

Bio create_new_bio(float Height,float Weight,int attack)
{
	Bio new_Bio;
	new_Bio.Poke_height=Height;
	new_Bio.Poke_weight=Weight;
	new_Bio.Attack=attack;
	return new_Bio;
}

Type create_new_type(char name[])
{
	Type new_Type;
	int length=strlen(name);
	new_Type.Typename=(char*)malloc(length+1);
	new_Type.effective_against_me=(Type**)malloc(0);
	new_Type.effective_against_others=(Type**)malloc(0);
	if(new_Type.Typename==NULL||new_Type.effective_against_me==NULL||new_Type.effective_against_others==NULL)
		{
			//in case one of the allocations failed-i will turn the type to null and return it
			new_Type.Typename=NULL;
			new_Type.effective_against_me=NULL;
			new_Type.effective_against_others=NULL;
			printf("Memory Problem");
			return new_Type;
		}
	//case allocation succed:
	strcpy(new_Type.Typename,name);
	new_Type.size_of_effective_against_me=0;
	new_Type.size_of_effective_against_others=0;
	new_Type.how_many=0;
	return new_Type;
}

Pokemon create_new_pokemon(char name[],char species[],Type* T,Bio bio)
{
	Pokemon new_Pokemon;
	int name_length=strlen(name);
	int species_length=strlen(species);
	new_Pokemon.Poke_name=(char*)malloc(name_length);
	new_Pokemon.Species=(char*)malloc(species_length);
	if(new_Pokemon.Poke_name==NULL||new_Pokemon.Species==NULL)
	{
		//in case one of the allocations failed-i will turn the name and species to null and return it
		new_Pokemon.Poke_name=NULL;
		new_Pokemon.Species=NULL;
		printf("Memory Problem");
		return new_Pokemon;
	}
	//case allocation succed:
	strcpy(new_Pokemon.Poke_name,name);
	strcpy(new_Pokemon.Species,species);

	new_Pokemon.Poke_type=T;
	new_Pokemon.Poke_bio=bio;
	T->how_many++;
	return new_Pokemon;
}

status free_type(Type* T)
{
	//=======================================================
	// in the Type_list,where there are effective against me and effective against others
	// the pointers are pointing inside the list-on each other
	// i hold point to them in the type_list-
	//so i will free one by one no need for free them in the effective against me list
	//=======================================================
	free(T->effective_against_me);
	free(T->effective_against_others);
	free(T->Typename);
	return success;
}
status free_pokemon(Pokemon* P)
{
		
		free(P->Poke_name);
		free(P->Species);
		return success;
}

status insert_type_to_type_list(Type_list* type_list1,Type* new_type)
{
	type_list1->T_size++;
	type_list1->T_list=(Type*)realloc(type_list1->T_list,type_list1->T_size*sizeof(Type));
	//Checking allocation succeed
	if(type_list1->T_list==NULL)
	{
		printf("Memory Problem");
		type_list1->T_size--;	
		return failure;
	}
	//if succeed-copying values of Type
	type_list1->T_list[type_list1->T_size-1]=*new_type;
	return success;
}
status insert_pokemon_to_pokemon_list(Pokemon_list* poke_list1,Pokemon* new_poke)
{
	poke_list1->P_size++;
	poke_list1->P_list=(Pokemon*)realloc(poke_list1->P_list,poke_list1->P_size*sizeof(Pokemon));
	//Checking allocation succeed
	if(poke_list1->P_list==NULL)
	{
		printf("Memory Problem");
		poke_list1->P_size--;
		return failure;
	}
	//if succeed-copying values of Type
	poke_list1->P_list[poke_list1->P_size-1]=*new_poke;
	return success;
}

status add_effective_against_me(Type* A,Type* B)
{
	A->size_of_effective_against_me++;
	A->effective_against_me=(Type**)realloc(A->effective_against_me,A->size_of_effective_against_me*sizeof(Type*));
	//checking allocating succeeed
	if(A->effective_against_me==NULL)
		{
			A->size_of_effective_against_me--;
			printf("Memory Problem");
			return failure;
		}
	//if succeed-changing the pointer inside the list to point B
	A->effective_against_me[A->size_of_effective_against_me-1]=B;
	return success;
}

status add_effective_against_others(Type* A,Type* B)
{
	A->size_of_effective_against_others++;
	A->effective_against_others=(Type**)realloc(A->effective_against_others,A->size_of_effective_against_others*sizeof(Type*));
	//checking allocating succeed
	if(!A->effective_against_others)
		{
			A->size_of_effective_against_others--;
			printf("Memory Problem");
			return failure;
		}
	//if succeed-changing the pointer inside the list to point B
	A->effective_against_others[A->size_of_effective_against_others-1]=B;
	return success;
}

status remove_effective_against_me(Type* A, Type* B)
{
    if (!A || !B || A->size_of_effective_against_me == 0)
    {
        return failure;
    }

    for (int i = 0; i < A->size_of_effective_against_me; i++)
    {
    	//realloc deletes from the end of the allocation!!
    	//we will bubble swap the pointers through A->effective_against_me- the last pointer in the allocation and the pointer to B Type
    	//all remaining is to realloc with smaller size(minus one sizeof(Type*))-and last pointer(the one thats points to B Type) will be deleted.

        if (A->effective_against_me[i]->Typename == B->Typename)
        {
			//Swap one by one for keep the order(Because the check needs the string to be exactly equal)
			//we could just do this:
			// A->effective_against_others[i] = A->effective_against_others[A->size_of_effective_against_others - 1];
			//but then the order will change
			Type* temp;
			for(int j=i+1;j<A->size_of_effective_against_me; j++)
			{
				temp=A->effective_against_me[i];
				A->effective_against_me[i]=A->effective_against_me[j];
				A->effective_against_me[j]=temp;
				i++;
			}	
		   A->size_of_effective_against_me--;	
		   //using temp array just in case of problem with alocations-For not losing current Data
            Type** temp_array = (Type**)realloc(A->effective_against_me, A->size_of_effective_against_me * sizeof(Type*));
            // Check if reallocation is successful
			if (!temp_array && A->size_of_effective_against_me > 0)
            {
                // Handle realloc failure
				printf("Memory Problem");
				A->size_of_effective_against_me++;	
                return failure;
            }
			//if succeed-update the original list
            A->effective_against_me = temp_array;
            return success;
        }
    }
    return failure; // Type B not found in the array.
}

status remove_effective_against_others(Type* A, Type* B)
{
	if (!A || !B || A->size_of_effective_against_others == 0)
	    {
	        return failure;
	    }

	    for (int i = 0; i < A->size_of_effective_against_others; i++)
	    {
	    	//realloc deletes from the end of the allocation!!
	    	//we will swap the pointers inside A->effective_against_others- the last pointer in the allocation and the pointer to B Type
	    	//all remaining is to realloc with smaller size(minus one sizeof(Type*))-and last pointer(the one thats points to B Type) will be deleted.

	        if (A->effective_against_others[i]->Typename == B->Typename)
	        {
				//Swap one by one for keep the order(Because the check needs the string to be exactly equal)
				//we could just do this:
				// A->effective_against_others[i] = A->effective_against_others[A->size_of_effective_against_others - 1];
				//but then the order will change
				Type* temp;
				for(int j=i+1;j<A->size_of_effective_against_others; j++)
				{
					temp=A->effective_against_others[i];
					A->effective_against_others[i]=A->effective_against_others[j];
					A->effective_against_others[j]=temp;
					i++;
				}		           
	            A->size_of_effective_against_others--;	     
				//using temp array just in case of problem with alocations-For not losing current Data
	            Type** temp_array = (Type**)realloc(A->effective_against_others, A->size_of_effective_against_others * sizeof(Type*));
	            // Check if reallocation is successful
				if (!temp_array && A->size_of_effective_against_others > 0)
	            {
	                // Handle realloc failure
					printf("Memory Problem");
					A->size_of_effective_against_others++;	
	                return failure;
	            }
				//if succeed-update the original list
	            A->effective_against_others = temp_array;
	            return success;
	        }
	    }
	    return failure; // Type B not found in the array.
	}
status print_pokemon(Pokemon* P)
{
	if(!P)
	{
		return failure;
	}
	printf("%s :\n%s, %s Type.\n",P->Poke_name,P->Species,P->Poke_type->Typename);
	printf("Height: %.2f m    Weight: %.2f kg    Attack: %d\n",P->Poke_bio.Poke_height,P->Poke_bio.Poke_weight,P->Poke_bio.Attack);
	printf("\n");
	return success;
}

status print_type(Type* T)
{
	if(!T)
	{
		return failure;
	}

	int i=0;
	printf("Type %s -- %d pokemons",T->Typename,T->how_many);

	if(T->how_many==0 && T->size_of_effective_against_me==0 && T->size_of_effective_against_others==0 )
	{
		printf("\n\n");
		return success;
	}

	if(T->size_of_effective_against_me!=0)
	{
		printf("\n\tThese types are super-effective against %s:",T->Typename);

		for( i=0;i<T->size_of_effective_against_me-1;i++)
		{
			printf("%s ,",T->effective_against_me[i]->Typename);
		}
		printf("%s",T->effective_against_me[i]->Typename);
	}
	if(T->size_of_effective_against_others!=0)
	{
		printf("\n\t%s moves are super-effective against:",T->Typename);
		for(i=0;i<T->size_of_effective_against_others-1;i++)
		{
			printf("%s ,",T->effective_against_others[i]->Typename);
		}
		printf("%s",T->effective_against_others[i]->Typename);
	}
	printf("\n\n");
	return success;
}







