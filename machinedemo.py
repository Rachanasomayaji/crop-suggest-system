import pandas as pd
import sklearn as sk
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
dataset=pd.read_csv('cpdata.csv')
print(type(dataset))
import pickle

x=dataset.iloc[ :,[0,1,2,3]].values
#print(x)
y=dataset.iloc[:,[4]].values
xtrain,xtest,ytrain,ytest = (train_test_split(x,y,test_size=0.25,random_state=1000))
classifier=KNeighborsClassifier( n_neighbors=4)
ytrain=np.ravel(ytrain)
classifier.fit(xtrain,ytrain)#traing is done


model=open('knnmodel.pkl','wb')#create a file and it going to Write bites
pickle.dump(classifier,model)#to dump frm classifier to model
model.close()
'''
tdata=np.array([[40, 100, 6.0 ,122]])
prediction=classifier.predict(tdata)
print(prediction)
'''

