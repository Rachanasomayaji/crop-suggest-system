from flask import Flask,render_template,request#F class
import sklearn as sk
import pickle
import numpy as np
app=Flask(__name__)
@app.route('/')#describe whos first,/=default page
def index():
    #return "<center>,<marquee><h1 style='color:blue;'> Welcome to flask</marqu</center></h1>"
    return render_template('index.html')


@app.route('\result')
def result():

    temp =float(request.args.get('temp'))
    hum = float(request.args.get('hum'))
    ph = float(request.args.get('ph'))
    rainfall = float(request.args.get('rainfall'))

    td=[[temp,hum,ph,rainfall]]
    file=open("knnmodel.pkl",'rb')

    testdata=np.array(td)




if __name__=='__main__':
   app.run(debug=True)
