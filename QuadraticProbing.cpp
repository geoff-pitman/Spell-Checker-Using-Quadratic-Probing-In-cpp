// Updated by: Geoffrey Pitman
// Author: Mark Allen Weiss (Data Structure and Algorithm Analysis 4e)
// Course: CSC402 - 010 - Data Structures 2
// Intructor: Dr. Zhang
// Due: 10/24/2016
// Project: 3
// File: QuadraticProbing.cpp
// Purpose:  To demonstrate the implementation of a hash-table
//           data structure using quadratic probing and <.5 load factor
#include <iostream>
#include "QuadraticProbing.h"
using namespace std;

/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}

/**
 * Internal method to return a prime number at least as large as n.
 * Assumes n > 0.
 */
int nextPrime( int n )
{
    if( n % 2 == 0 )
        n++;

    for( ; !isPrime( n ); n += 2 )
        ;

    return n;
}

/**
 * A hash routine for string objects.
 */
int hash( const string & key )
{
    int hashVal = 0;

    for( int i = 0; i < key.length( ); i++ )
        hashVal = 37 * hashVal + key[ i ];

    return hashVal;
}

/**
 * A hash routine for ints.
 */
int hash( int key )
{
    return key;
}
