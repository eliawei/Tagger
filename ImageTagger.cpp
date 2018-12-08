//
// Created by elia on 05-Dec-18.
//

#include "ImageTagger.h"

ImageTagger::ImageTagger(int seg_limit){}
ImageTagger::~ImageTagger(){}
void ImageTagger::add_image(int image_id){}
void ImageTagger::delete_image(int image_id){}

void ImageTagger::add_label(int image_id, int seg_id, int label) {
    Image* image = new Image(this->seg_limit);
    image = (Image*)this->images.find(image_id);

    image->add_label(seg_id, label);
}

int ImageTagger::get_label(int image_id,int seg_id) {
    Image* image = new Image(this->seg_limit);
    image = (Image*)this->images.find(image_id);

    return image->get_label(seg_id);
}

void ImageTagger::delete_label(int image_id,int seg_id) {
    Image* image = new Image(this->seg_limit);
    image = (Image*)this->images.find(image_id);

    image->delete_label(seg_id);
}

int* ImageTagger::get_all_unlabled_segments(int image_id, int* numOfSegments){}

int* ImageTagger::get_all_segments_by_label(int label, int* numOfSegments) {

}