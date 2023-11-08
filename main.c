#include <stdio.h>
#include <stdlib.h>  // malloc için
#include <string.h>

#define MAX_FAMILY_MEMBERS 10 //aile
#define HASH_TABLE_SIZE 26 //bellek boyutu

const char* familyMembers[MAX_FAMILY_MEMBERS] = {
        "umut","berhat","rozerin",
        "kani","Mustafa","Zeynep",
        "sezai","icardi","aynur",
        "begum"
};

// Hash tablosu için veri yapısı
typedef struct HashEntry {
    const char* key;
    int value;
    struct HashEntry* next;
} HashEntry;

// Hash tablosu
HashEntry* hashTable[HASH_TABLE_SIZE];

// Karakterlerin ASCII değerlerini toplayıp tablonun boyutuna göre mod aldım
int hashFunction(const char* key) {
    int total = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        total += (int)key[i];
    }
    return total % HASH_TABLE_SIZE;
}

// Hash tablosuna veriyi eklemek kodu
void put(const char* key, int value) {
    int index = hashFunction(key);
    HashEntry* islem_area = hashTable[index];
    if (islem_area == NULL) {
        islem_area = (HashEntry*)malloc(sizeof(HashEntry));
        islem_area->key = key;
        islem_area->value = value;
        islem_area->next = NULL;
        hashTable[index] = islem_area;
    } else {
        // Çakışma durumunu çözmek için aşağıdaki yöntemi yazdım
        while (islem_area->next != NULL) {
            islem_area = islem_area->next;
        }
        islem_area->next = (HashEntry*)malloc(sizeof(HashEntry));
        islem_area = islem_area->next;
        islem_area->key = key;
        islem_area->value = value;
        islem_area->next = NULL;
    }
}

// Veriyi hash tablosundan getiren fonksiyonun kodu
int get(const char* key) {
    int index = hashFunction(key);
    HashEntry* current = hashTable[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return -1; // Anahtar (key) bulunamazsa -1 döndürecek
}

int main(void) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }

    // Aile üyelerinin isimlerini ve verilerini hash tablosuna ekleme işlemi
    for (int i = 0; i < MAX_FAMILY_MEMBERS; i++) {
        put(familyMembers[i], i);
    }

    // Hash tablosunu veriyi yazdırdım
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        HashEntry* current = hashTable[i];
        while (current != NULL) {
            printf("Index %d: %s -> %d\n", i, current->key, current->value);
            current = current->next;
        }
    }

    // Belleği temizle
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        HashEntry* current = hashTable[i];
        while (current != NULL) {
            HashEntry* temp = current;
            current = current->next;
            free(temp);
        }
    }

    return 0;
}

