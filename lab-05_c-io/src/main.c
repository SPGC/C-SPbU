#include <string.h>
#include <stdio.h>
#include <math.h>

#include "point_list.h"


typedef int (*reader)(FILE *file, intrusive_list *list);

// Чтение данных из файла заданной спецификации:
// fmt - формат файла (r - текстовый файл, rb - бинарный файл)
// file_name - имя входного файла
// list - список для записи данных
// reader - функция чтения
int file_reader(char *fmt, char *file_name, intrusive_list *list, reader reader){
    FILE* input = fopen(file_name, fmt);
    if(!input){
        return -1;
    }
    int result = reader(input, list);
    fclose(input);
    return result;
}

// Чтение данных из текстового файла
// file - входной файл
// list - список для записи данных
int text_reader(FILE *file, intrusive_list *list){
    int x, y, flag;
    while (fscanf(file, "%d %d", &x, &y) == 2) {
        flag = add_point(list, x, y);
        if(flag)
        {
            return -1;
        }
    }
    return 0;
}

// Перевод трех байт в integer
// binary - массив байт
int parse_int(const unsigned char* binary) {
    int result = 0;
    for (int i = 0; i < 3; i++) {
        result |= ((int)binary[i]) >> (8 * i);
    }
    if (binary[2] & 0x80) {
        result |= 0xFF000000;
    }
    return result;
}

// Чтение данных из бинарного файла
// file - входной файл
// list - список для записи данных
int bin_reader(FILE *file, intrusive_list *list){
    int x, y, flag;
    unsigned char input_data[6];
    while (fread(input_data, sizeof(unsigned char), 6, file) == 6) {            
        x = parse_int(&input_data[0]);
        y = parse_int(&input_data[3]);
        flag = add_point(list, x, y);
        if(flag){
            return -1;
        }
    } 
    return 0;
}

// Запись данных в файл заданной спецификации:
// fmt - формат файла (w - текстовый файл, wb - бинарный файл)
// op - функция записи
// list - список с данными
// output_name - имя выходного файла
int file_writer(const char *fmt, operation op, intrusive_list *list,
                 const char *output_name){
    FILE* output = fopen(output_name, fmt);
    if(!output){
        remove_all_points(list);
        return -1;
    }
    apply(list, op, (void*)output);
    fclose(output);
    remove_all_points(list);
    return 0;
}

// Запись текстового файла
// node - записываемая нода
// output - выходной файл
void write_text(intrusive_node* node, void* output) {
    point* writing_point = container_of(node, point, node);
    fprintf((FILE*)output, "%d %d\n", writing_point->x, writing_point->y);
}

// Преобразование integer в три байта, значения четвертого байта отбрасываются
void int_to_bin(const int n, unsigned char* const binary) {
    for (int i = 0; i < 3; i++) {
        binary[i] = (unsigned char)((n >> (8 * i)));
    }
}

// Запись бинарного файла
// list - список с данными
// output - выходной файл
void write_bin(intrusive_node *node, void* output) {
    point* writing_point = container_of(node, point, node);  
    unsigned char result[3];
    int_to_bin(writing_point->x, result);
    fwrite(result, sizeof(unsigned char), 3, (FILE*)output);
    int_to_bin(writing_point->y, result);
    fwrite(result, sizeof(unsigned char), 3, (FILE*)output);
}

int main(int argc, char** argv) {
    if (argc < 3 || argc > 5){
        return -1;
    }
    intrusive_list list;
    init_list(&list);
    int reader_flag;
    if (strcmp(argv[1], "loadtext") == 0) {
        reader_flag = file_reader("r", argv[2], &list, text_reader);
    } else if (strcmp(argv[1], "loadbin") == 0) {
        reader_flag = file_reader("rb", argv[2], &list, bin_reader);
    } else {
        return -1;
    }
    if (reader_flag){
        return -1;
    }
    if (strcmp(argv[3], "savetext") == 0) {
        return file_writer("wb", write_bin, &list, argv[4]);
    } else if (strcmp(argv[3], "savebin") == 0) {
        return file_writer("wb", write_bin, &list, argv[4]);
    } else if (strcmp(argv[3], "print") == 0) {
        apply(&list, print_point, argv[4]);
        printf("\n");
    } else if (strcmp(argv[3], "count") == 0) {
        int length = get_length(&list); // Метод реализован через apply в clist.c
        printf("%d\n", length);
    } else {
        return -1;
    }
    remove_all_points(&list);
    return 0;
}