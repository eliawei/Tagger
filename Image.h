//
// Created by elia on 05-Dec-18.
//

#ifndef TAGGER_IMAGE_H
#define TAGGER_IMAGE_H

#include "List.h"


class Image {
private:
    int* segments;
    int seg_num;
    void** pointers;
    List<int,int> not_labled;
public:
    Image(int seg_num);
    ~Image();
    void add_label(int seg_id,int label);
    int get_label(int seg_id);
    void delete_label(int seg_id);
    int* get_all_unlabled_segments(int* numOfSegments);
    int* get_all_segments_by_label(int label, int* numOfSegments);
};


#endif //TAGGER_IMAGE_H
