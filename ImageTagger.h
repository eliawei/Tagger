//
// Created by elia on 05-Dec-18.
//

#ifndef TAGGER_IMAGETAGGER_H
#define TAGGER_IMAGETAGGER_H

#include "AVL_Tree.h"
#include "Image.h"

class ImageTagger {
private:
    AVL_Tree<int,Image> images;
    int seg_limit;
public:
    ImageTagger(int seg_limit);
    ~ImageTagger();
    int get_size() {return this->images.getSize();};
    int get_seg_lim() {return this->seg_limit;}
    void add_image(int image_id);
    void delete_image(int image_id);
    void add_label(int image_id, int seg_id, int label);
    int get_label(int image_id, int seg_id);
    void delete_label(int image_id, int seg_id);
    int* get_all_unlabled_segments(int image_id, int* numOfSegments);
    int* get_all_segments_by_label(int label, int* numOfSegments);
};


#endif //TAGGER_IMAGETAGGER_H
