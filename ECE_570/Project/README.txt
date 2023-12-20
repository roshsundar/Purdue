To run the experiments:
1) Download the dataset present at: https://github.com/Ironbrotherstyle/PCB-DATASET
	- This dataset is a collection of  1386 images with 6 types of identifiable defects for the use of 	 	  detection, classification, and registration tasks.
2) Extract training defects for SVM by running training_defect_isolator.py
3) Run SVM.py to train the SVM model to classify defects
4) Provide a reference and defective PCB image from the dataset in the same directory
5) Run defect_detection.py to isolate and classify defects using model

training_defect_isolator.py, SVM.py, and defect_detection.py were not taken from any repository.
All code is original, though inspiration was taken from other implementation code and documentation examples.