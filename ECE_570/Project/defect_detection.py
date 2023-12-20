import cv2
import numpy as np
from sklearn.externals import joblib
from sklearn.svm import SVC
from sklearn.cluster import KMeans

def rotate(Reference , Defect): 
    height, width = Reference.shape

    # Find key points and descriptors in both images 
    orb_detector = cv2.ORB_create(5000) 
    keypoints1, descriptors1 = orb_detector.detectAndCompute(Defect, None) 
    keypoints2, descriptors2 = orb_detector.detectAndCompute(Reference, None)

    # Match descriptors using a brute force matcher 
    matcher = cv2.BFMatcher(cv2.NORM_HAMMING, crossCheck = True) 
    matches = matcher.match(descriptors1, descriptors2)

    # Sort matches by distance 
    matches = sorted(matches, key=lambda x: x.distance)
    matches = matches[:int(len(matches)*90)] 
    no_of_matches = len(matches) 
    p1 = np.zeros((no_of_matches, 2)) 
    p2 = np.zeros((no_of_matches, 2)) 
    
    # Map the descriptors
    for i in range(len(matches)): 
        p1[i, :] = keypoints1[matches[i].queryIdx].pt 
        p2[i, :] = keypoints2[matches[i].trainIdx].pt 
    
    # Find transformation matrix that decribes the descriptor mapping
    homography, _ = cv2.findHomography(p1, p2, cv2.RANSAC)

    # Orient the Defect image the same way as the reference image
    transformed_img = cv2.warpPerspective(Defect, homography, (width, height)) 
    return transformed_img

# Path strings
Ref_path = "C:/Users/roshs/Downloads/Reference.jpg"
Def_path = "C:/Users/roshs/Downloads/Rotated.jpg"
Visual_path = "C:/Users/roshs/Downloads/Defect.jpg"

# Load the saved model
model_filename = "svm_classifier_model.joblib"
classifier = joblib.load(model_filename)

# Load the two images
Reference = cv2.imread(Ref_path, cv2.IMREAD_GRAYSCALE)
Defect = cv2.imread(Def_path, cv2.IMREAD_GRAYSCALE)

Defect = rotate(Reference, Defect)

# Ensure both images have the same dimensions
if Reference.shape != Defect.shape:
    raise ValueError("The input images must have the same dimensions.")

# Compute the absolute difference between the images
difference = cv2.absdiff(Reference, Defect)

# Define a threshold to filter out minor differences
threshold = 30

# Apply a blur filter to reduce noise
blurred = cv2.GaussianBlur(difference, (1, 1), 0)

# Create a binary image where pixels with differences greater than the threshold are white
_, thresholded = cv2.threshold(blurred, threshold, 255, cv2.THRESH_BINARY)

# Use morphological processing for noise reduction
kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (3, 3))
thresholded = cv2.morphologyEx(thresholded, cv2.MORPH_CLOSE, kernel)

# Find contours in the thresholded image
contours, _ = cv2.findContours(thresholded, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Remove very small contours as these are likely to be noise
contours = [contour for contour in contours if cv2.contourArea(contour) > 3]

# Draw rectangles around the areas of difference on a copy of the original image
image_with_differences =  cv2.imread(Visual_path)

for contour in contours:
    x, y, w, h = cv2.boundingRect(contour)
    cv2.rectangle(image_with_differences, (x, y), (x + w, y + h), (0, 0, 255), 3)

    # Extract the region from the original Defect image
    extracted_region = Defect[y:y+h, x:x+w]

    # Preprocessing
    extracted_region = cv2.cvtColor(extracted_region, cv2.COLOR_BGR2RGB)
    extracted_region = cv2.resize(extracted_region, (64, 64))

    # Extract SIFT features
    sift = cv2.SIFT_create()
    _, new_desc = sift.detectAndCompute(extracted_region, None)

    # Bag-of-Features Representation
    kmeans = KMeans(n_clusters=50) 
    if new_desc is not None:
        new_cluster_assignments = kmeans.predict(new_desc)
        new_hist, _ = np.histogram(new_cluster_assignments, bins=range(51))
    else:
        new_hist = np.zeros(50)  # Default histogram if no features are detected

    # Scaling (if used during training)
    # If you used StandardScaler during training, apply it here
    # new_hist = scaler.transform([new_hist])  # Assuming 'scaler' is the trained StandardScaler

    # Prediction
    predicted_label = classifier.predict([new_hist])

    print("Predicted Label:", predicted_label[0])


# Display the images with differences
image_with_differences = cv2.resize(image_with_differences, (1213, 634)) 
cv2.imshow("Differences", image_with_differences)
cv2.waitKey(0)
cv2.destroyAllWindows()