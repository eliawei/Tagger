//
// Created by Gchiko on 08-Dec-18.
//
#include "library2.h"
#include "ImageTagger.h"

void *Init(int segments) {
    if (segments <= 0) {
        return NULL;
    }
    ImageTagger *DS = new ImageTagger(segments);
    return (void *) DS;
}

StatusType AddImage(void *DS, int imageID) {
    if (!DS || imageID <= 0) {
        return INVALID_INPUT;
    }
    if (DS != NULL) {
        try {
            ((ImageTagger *) DS)->add_image(imageID);
        } catch (bad_alloc &ba) {
            return ALLOCATION_ERROR;
        } catch (already_exists &ae) {
            return FAILURE;
        }

        return SUCCESS;


    }
}

StatusType DeleteImage(void *DS, int imageID) {
    if (DS == NULL || imageID <= 0) {
        return INVALID_INPUT;
    }
    try {
        ((ImageTagger *) DS)->delete_image(imageID);
    } catch (bad_alloc &ba) {
        return ALLOCATION_ERROR;
    } catch (not_found &nf) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType AddLabel(void *DS, int imageID, int segmentID, int label) {

    int seg_lim;
    if (DS != NULL) {
        seg_lim = ((ImageTagger *) DS)->get_seg_lim();
    }

    if (DS == NULL || segmentID >= seg_lim || segmentID < 0 ||
        imageID <= 0 || label <= 0) {
        return INVALID_INPUT;
    }

    try {
        ((ImageTagger *) DS)->add_label(imageID, segmentID, label);
    } catch (bad_alloc &ba) {
        return ALLOCATION_ERROR;
    } catch (not_found &nf) {
        return FAILURE;
    } catch (already_labeled &al) {
        return FAILURE;
    }

    return SUCCESS;
}

StatusType GetLabel(void *DS, int imageID, int segmentID, int *label) {
    ImageTagger *im_tag;
    int seg_lim;

    if (DS == NULL || segmentID < 0 ||
        imageID <= 0 || label == NULL) {
        return INVALID_INPUT;
    }

    im_tag = (ImageTagger *) DS;
    seg_lim = im_tag->get_seg_lim();

    if (segmentID >= seg_lim) {
        return INVALID_INPUT;

    }

    try {
        *label = im_tag->get_label(imageID, segmentID);
    } catch (not_found &nf) {
        return FAILURE;
    } catch (not_labeled &nl) {
        return FAILURE;
    }

    return SUCCESS;
}

StatusType DeleteLabel(void *DS, int imageID, int segmentID) {
    ImageTagger *im_tag;
    int seg_lim;


    if (DS == NULL || segmentID < 0 || imageID <= 0) {
        return INVALID_INPUT;
    }

    im_tag = (ImageTagger *) DS;
    seg_lim = im_tag->get_seg_lim();

    if (segmentID >= seg_lim) {
        return INVALID_INPUT;
    }

    try {
        im_tag->delete_label(imageID, segmentID);
    } catch (not_found &nf) {
        return FAILURE;
    } catch (not_labeled &nl) {
        return FAILURE;
    }

    return SUCCESS;
}

StatusType GetAllUnLabeledSegments(void *DS, int imageID, int **segments,
                                   int *numOfSegments) {
    if (!DS || imageID <= 0 || !segments || !numOfSegments) {
        return INVALID_INPUT;
    }
    try {
        ImageTagger *im_tag;
        im_tag = (ImageTagger *) DS;
        *segments = (im_tag->get_all_unlabled_segments(imageID,
                                                       numOfSegments));

    } catch (not_found &nf) {
        return FAILURE;
    } catch (all_labeled &al) {
        return FAILURE;
    }

    return SUCCESS;
}

StatusType
GetAllSegmentsByLabel(void *DS, int label, int **images, int **segments,
                      int *numOfSegments) {}

void Quit(void **DS) {
    if (DS == NULL) return;
    delete ((ImageTagger *) *DS);
    *DS = NULL;

}

