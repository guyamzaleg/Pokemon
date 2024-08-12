/*
 ============================================================================
 Name        : Pokemon.h
 Author      : Guy Amzaleg
 Version     :
 Copyright   :
 Description :	includes All functions Signatures Declarations And All structs defines
 ============================================================================
*/
#ifndef POKEMON_H
#define POKEMON_H
#include "Defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//==============================================================
//Struct defines
//==============================================================

//Type
/* Type Struct -----------Size in stack Segment 4+4+4+4+4+4=24 bytes-------------
	contains:
	  		Typename:name of Type in char array
			how_many:how many pokemons inside as int
			effective_against_me:pointer to list of pointers dinamiclly allocated of effective types against me
			effective_against_others:pointer to list of pointers dinamiclly allocated of the types the Type effective against.
			size_of_effective_against_me:how many types currently in the list
			size_of_effective_against_others:how many types currently in the list
*/
typedef struct t_type
{
	char* Typename;
	int how_many;
	struct t_type** effective_against_me;
	int size_of_effective_against_me;
	struct t_type** effective_against_others;
	int size_of_effective_against_others;

} Type;


//Bio
/* Bio Struct -----------Size in stack Segment 4+4+4=12 bytes-------------
	contains:
  			Poke_height:height of the pokemon inside a float
			Poke_weight:weight of the pokemon inside a float
			Attack:Attack Rate of the pokemon inside a int

 */
typedef struct b_bio
{	
	float Poke_height;
	float Poke_weight;
	int Attack;
} Bio;


//Pokemon
/* Pokemon Struct -----------Size in stack Segment 4+4+4+12=24 bytes-------------
	contains:
		  		Poke_name:name of The Pokemon in pointer to char array
				Species:name of The Pokemns Species in pointer to char array
				how_many:how many pokemons inside as int
				Poke_Type: pointer to Pokemons Type(A struct previosly defined)
				Poke_bio: Pokemons Bio(A struct previosly defined)
*/
typedef struct p_pokemon
{
	char* Poke_name;
	char* Species;
	Type* Poke_type;
	Bio Poke_bio;
} Pokemon;


//Pokemon_list
/*Poke_list Struct -----------Size in stack Segment 4+4=8 bytes-------------
   contains:
  			P_list:pointer to first Pokemon in Pokemons array in the heap memory
			P_size:number of Pokemons currently in the list
 */
typedef struct list_of_pokemons
{
	Pokemon* P_list;
	int P_size;
} Pokemon_list;


//Type_list
/* Type_list Struct-----------Size in stack Segment 4+4=8 bytes-------------
	 contains:
	  			T_list:pointer to first Type in Types array in the heap memory
				T_size:number of Types currently in the list
*/
typedef struct list_of_types
{
	Type* T_list;
	int T_size;
} Type_list;


//==============================================================
//Pokemon Function Declarations and General Explanation
//==============================================================

//input:float Hight ,float Weight , int attack
//output: Create and reutrn new Bio Struct
Bio create_new_bio(float Height,float Weight,int attack);

//input: name:char array(string)
//output:  Create and reutrn new Bio Struct
Type create_new_type(char name[]);

//input: name,species -char array(string) , type-A pointer to Type struct , bio -struct Bio
//output: Create and reutrn new Pokemon Struct
Pokemon create_new_pokemon(char name[],char species[],Type* type,Bio bio);

//input:
//output: create and return empty Type_list struct 
Type_list create_empty_type_list();

//input:type_list1-A pointer to struct Type_list ,new_type-A pointer to Type
//output: insert new_type into type_list1 and return proccess status
status insert_type_to_type_list(Type_list* type_list1,Type* new_type);

//input:
//output: create empty Pokemon_list struct 
Pokemon_list create_empty_pokemon_list();

//input:poke_list1-A pointer to struct Pokemon_list ,new_poke-A pointer to Pokemon
//output: insert new_poke into poke_list1 and return proccess status
status insert_pokemon_to_pokemon_list(Pokemon_list* poke_list1,Pokemon* new_poke);

//input:A,B-Type Pointers
//output: insert B into the effective_against_me list of A and return proccess status
status add_effective_against_me(Type* A,Type* B);

//input:A,B-Type Pointers
//output: insert B into the effective_against_others list of A and return proccess status
status add_effective_against_others(Type* A,Type* B);

//input:A,B-Type Pointers
//output: removes B from the effective_against_me list of A and return proccess status
status remove_effective_against_me(Type* A,Type* B);

//input:A,B-Type Pointers
//output: removes B from the effective_against_others list of A and return proccess status
status remove_effective_against_others(Type* A, Type* B);

//input:P-Pointer to Pokemon
//output:prints the Pokemon as requested and return proccess status
status print_pokemon(Pokemon* P);

//input:P-Pointer to Type
//output:prints the type as requested and return proccess status
status print_type(Type* T);

//Free Function Declarations

//input:T-Pointer to Type
//output: free all the memory allocated for T and return proccess status
status free_type(Type* T);

//input:P-Pointer to Pokemon
//output: free all the memory allocated for P and return proccess status
status free_pokemon(Pokemon* P);

//input:T_L-Pointer to Type_list
//output: free all the memory allocated for T_L (using function free_type) and return proccess status
status free_type_list(Type_list* T_L);

//input:P_L-Pointer to Pokemon_list
//output: free all the memory allocated for P_L (using function free_pokemon) and return proccess status
status free_pokemon_list(Pokemon_list* P_L);




#endif

