from sklearn.model_selection import train_test_split
from sklearn.svm import SVC
from sklearn.cluster import KMeans
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import make_pipeline
from sklearn.metrics import accuracy_score
from sklearn.externals import joblib
import cv2
import numpy as np
import os

data_path = "C:\Purdue\\2023_Fall\ECE_570\\training_defects"

# Assuming 'data' is a list of 64x64 images
data = []
# 'labels' is a 1D array containing the corresponding labels (0 to 5 in your case)
# 4 images loaded
labels = []

for filename in os.listdir(data_path):
    img_path = os.path.join(data_path, filename)
    img = cv2.imread(img_path)  # Read images in color
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)  # Convert BGR to RGB if needed
    data.append(img)
    labels.append(int(filename[0]))

# Step 1: Feature extraction
sift = cv2.SIFT_create()

# Extract SIFT features from each image
features = []
for img in data:
    _, desc = sift.detectAndCompute(img, None)
    if desc is not None:
        features.append(desc)

# Convert the list of feature descriptors into a numpy array
features = np.vstack(features)

# Step 2: Bag-of-Features Representation
kmeans = KMeans(n_clusters=50)  # Adjust the number of clusters based on your dataset
kmeans.fit(features)

def bag_of_features_representation(img):
    _, desc = sift.detectAndCompute(img, None)
    if desc is not None:
        # Assign each feature to the nearest cluster
        cluster_assignments = kmeans.predict(desc)
        # Create a histogram of cluster frequencies
        hist, _ = np.histogram(cluster_assignments, bins=range(51))
        return hist
    else:
        # Return a default histogram if no features are detected
        return np.zeros(50)

# Create bag-of-features representations for all images
bof_representations = [bag_of_features_representation(img) for img in data]

# Step 3: Classifier
X_train, X_test, y_train, y_test = train_test_split(bof_representations, labels, test_size=0.2, random_state=42)

# Use a Support Vector Machine (SVM) classifier
classifier = make_pipeline(StandardScaler(), SVC(kernel='linear', C=1.0))
classifier.fit(X_train, y_train)

# Make predictions on the test set
predictions = classifier.predict(X_test)

# Evaluate the accuracy
accuracy = accuracy_score(y_test, predictions)
print("Accuracy:", accuracy)

# Save the trained classifier to a file
model_filename = "svm_classifier_model.joblib"
joblib.dump(classifier, model_filename)
print("Model saved to:", model_filename)