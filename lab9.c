#include <stdio.h>
#include <stdlib.h>

typedef struct RecordType {
    int id;
    char name;
    int order;
    struct RecordType* next; // pointer to next record in the same hash bucket
} RecordType;

typedef struct HashType {
    RecordType** buckets; // array of pointers to records
    int size;
} HashType;

// function to compute the hash of an integer key
int hash(int key, int tableSize) {
    return key % tableSize;
}

// function to parse the input file into an array of RecordType
int parseData(char* inputFileName, RecordType** ppData) {
    FILE* inFile = fopen(inputFileName, "r");
    if (inFile == NULL) {
        fprintf(stderr, "Failed to open file\n");
        return 0;
    }

    int dataSz = 0;
    int id, order;
    char name;
    RecordType* pRecord;

    // scan the number of records from the first line in the file
    fscanf(inFile, "%d\n", &dataSz);

    // allocate memory for the array of rescords
    *ppData = (RecordType*)malloc(sizeof(RecordType) * dataSz);
    if (*ppData == NULL) {
        fprintf(stderr, "Cannot allocate memory\n");
        exit(EXIT_FAILURE);
    }

    // read the records from the file
    for (int i = 0; i < dataSz; ++i) {
        pRecord = *ppData + i; // get the address of the i-th record
        
        // read the record on this line and store it in the i-th record struct 
        fscanf(inFile, "%d %c %d ", &id, &name, &order);
        pRecord->id = id;
        pRecord->name = name;
        pRecord->order = order;
        pRecord->next = NULL; // Initialize the next pointer to NULL
    }

    fclose(inFile);

    // return the number of records
    return dataSz;
}

// function to insert records into the hash table
void insertToHashTable(HashType* hashTable, RecordType* record) {
    // compute the index of the bucket
    int index = hash(record->id, hashTable->size);

    record->next = hashTable->buckets[index];
    hashTable->buckets[index] = record;
}

// function to create and initialize hash table
HashType* createHashTable(int size) {
    HashType* newTable = (HashType*)malloc(sizeof(HashType));
    if (newTable == NULL) {
        fprintf(stderr, "Failed to allocate memory for hash table\n");
        exit(EXIT_FAILURE);
    }

    newTable->size = size;

    newTable->buckets = (RecordType**)calloc(size, sizeof(RecordType*));
    if (newTable->buckets == NULL) {
        fprintf(stderr, "Failed to allocate memory for buckets\n");
        free(newTable);
        exit(EXIT_FAILURE);
    }

    return newTable;
}

// function to print all records in the hash table
void displayRecordsInHash(HashType* hashTable) {
    printf("Hash Table Contents:\n");

    // loop through all buckets
    for (int i = 0; i < hashTable->size; i++) {
        RecordType* current = hashTable->buckets[i]; // get the ith bucket
        if (current != NULL) { // if there is a record in the bucket
            printf("Bucket %d:", i); // print the bucket id
            
            // loop through all the records in the bucket till current is NULL
            while (current != NULL) {
                printf(" -> %d %c %d", current->id, current->name, current->order);
                current = current->next;
            }

            // space for next bucket
            printf("\n");
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <inputfile>\n", argv[0]);
        return EXIT_FAILURE;
    }

    RecordType* records;
    int recordCount = parseData(argv[1], &records);

    // size can be changed to increase efficiency by creating more buckets therfore more unique hash values
    HashType* hashTable = createHashTable(33); // seems to be the most optimal amount of buckets on this input when using the hash function provided

    // for each record, insert it into the hash table
    for (int i = 0; i < recordCount; i++) {
        insertToHashTable(hashTable, &records[i]);
    }

    // display the records in the hash table
    displayRecordsInHash(hashTable);

    // new safety trick
    return EXIT_SUCCESS;
}
