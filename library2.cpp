//
// Created by Gchiko on 08-Dec-18.
//
#include "library2.h"
#include "ImageTagger.h"

void *Init(int segments);

//StatusType AddImageק(void *DS, int imageID){}

//StatusType DeleteImage(void *DS, int imageID){}

StatusType AddLabel(void *DS, int imageID, int segmentID, int label) {
    ImageTagger* im_tag;
    int seg_lim;

    if (DS != NULL) {
        im_tag = (ImageTagger*)DS;
        seg_lim = im_tag->get_seg_lim();
    }

    if (segmentID >= seg_lim || segmentID <0 ||
        DS == NULL || imageID <= 0 || label <= 0) {
        return INVALID_INPUT;
    }

    try {
        im_tag->add_label(imageID, segmentID, label);
    } catch (bad_alloc& ba) {
        return ALLOCATION_ERROR;
    } catch (not_found& nf) {
        return FAILURE;
    } catch (all_labeled& al) {
        return FAILURE;
    }

    return SUCCESS;
}

StatusType GetLabel(void *DS, int imageID, int segmentID, int *label) {
    ImageTagger* im_tag;
    int seg_lim;

    if (DS != NULL) {
        im_tag = (ImageTagger*)DS;
        seg_lim = im_tag->get_seg_lim();
    }

    if (segmentID >= seg_lim || segmentID <0 ||
        DS == NULL || imageID <= 0 || label == NULL) {
        return INVALID_INPUT;
    }

    try {
        *label = im_tag->get_label(imageID, segmentID);
    } catch (not_found& nf) {
        return FAILURE;
    } catch (not_labeled& nl) {
        return FAILURE;
    }

    return SUCCESS;
}

StatusType DeleteLabel(void *DS, int imageID, int segmentID) {
    ImageTagger* im_tag;
    int seg_lim;

    if (DS != NULL) {
        im_tag = (ImageTagger*)DS;
        seg_lim = im_tag->get_seg_lim();
    }

    if (segmentID >= seg_lim || segmentID <0 ||
        DS == NULL || imageID <= 0 ) {
        return INVALID_INPUT;
    }

    try {
        im_tag->delete_label(imageID, segmentID);
    } catch (not_found& nf) {
        return FAILURE;
    } catch (not_labeled& nl) {
        return FAILURE;
    }

    return SUCCESS;
}

//StatusType GetAllUnLabeledSegments(void *DS, int imageID, int **segments, int *numOfSegments){}

//StatusType GetAllSegmentsByLabel(void *DS, int label, int **images, int **segments, int *numOfSegments){}

//void Quit(void** DS){}
