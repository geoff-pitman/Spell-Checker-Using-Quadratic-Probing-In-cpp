// Updated by: Geoffrey Pitman
// Author: Mark Allen Weiss (Data Structure and Algorithm Analysis 4e)
// Course: CSC402 - 010 - Data Structures 2
// Intructor: Dr. Zhang
// Due: 10/24/2016
// Project: 3
// File: QuadraticProbing.h
// Purpose:  To demonstrate the implementation of a hash-table
//           data structure using quadratic probing and <.5 load factor
#ifndef QUADRATICPROBING_GEOFFREYPITMAN_H
#define QUADRATICPROBING_GEOFFREYPITMAN_H

#include <vector>
#include <string>
#include <iomanip>
using namespace std;

int nextPrime( int n );

// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// int hash( string str ) --> Global method to hash strings
// void makeEmpty( )      --> Remove all items
// void printCollisions() --> Print total collisions for table
// void printLoadFactor(double n)  --> Print table load factor

template <typename HashedObj>
class HashTable
{
  public:
    explicit HashTable( int size = 101 ) : array( nextPrime( size ) )
      { makeEmpty( ); collisions = 0; }

    bool contains( const HashedObj & x )
    {
        return isActive( findPos( x ) );
    }
	
	void printLoadFactor(double n)
	{
		cout << setprecision(2) << "The load factor is " <<  n/array.size() << endl; 
	}
	void printCollisions()
	{
		cout << "There are in total " << collisions <<  " collisions during initialization." << endl;
	}
    void makeEmpty( )
    {
        currentSize = 0;
        for( int i = 0; i < array.size( ); i++ )
            array[ i ].info = EMPTY;
		collisions = 0;
    }

    bool insert( const HashedObj & x )
    {
            // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        array[ currentPos ] = HashEntry( x, ACTIVE );
            // Rehash; see Section 5.5
        if( ++currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }

    bool remove( const HashedObj & x )
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;

        array[ currentPos ].info = DELETED;
        return true;
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };

  private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry( const HashedObj & e = HashedObj( ), EntryType i = EMPTY )
          : element( e ), info( i ) { }
    };
    
    vector<HashEntry> array;
    int currentSize, collisions;


    bool isActive( int currentPos )
      { return array[ currentPos ].info == ACTIVE; }

    int findPos( const HashedObj & x )
    {
        int offset = 1;
        int currentPos = myhash( x );

        while( array[ currentPos ].info != EMPTY && array[ currentPos ].element != x )
        {
			currentPos += offset;  // Compute ith probe
			collisions++;
            offset += 2;
            if( currentPos >= array.size( ) )
                currentPos -= array.size( );
        }

        return currentPos;
    }
    void rehash( )
    {
		cout << "Rehashing...";
        vector<HashEntry> oldArray = array;

            // Create new double-sized, empty table
        array.resize( nextPrime( 2 * oldArray.size( ) ) );
        for( int j = 0; j < array.size( ); j++ )
            array[ j ].info = EMPTY;

            // Copy table over
        currentSize = 0;
        for( int i = 0; i < oldArray.size( ); i++ )
            if( oldArray[ i ].info == ACTIVE )
                insert( oldArray[ i ].element );
			
		cout << "New size is " << array.size() << endl;
    }
    int myhash( const HashedObj & x )
    {
        int hashVal = hash( x );

        hashVal %= array.size( );
        if( hashVal < 0 )
            hashVal += array.size( );

        return hashVal;
    }
};

int hash( const string & key );
int hash( int key );

#endif