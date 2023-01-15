import sklearn as sk
import pickle
import numpy as np
file=open("knnmodel.pkl",'rb')
model=pickle.load(file)
testdata=np.array([[29,222,6.6,200]])
prediction=model.predict(testdata)
print(prediction[0])
