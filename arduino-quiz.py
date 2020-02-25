#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""A simple script to generate quiz for arduino.
"""

import json
import os
import requests
import serial

__author__ = "Giuseppe Caliendo"
__copyright__ = "Copyright 2020, Giuseppe Caliendo"
__credits__ = ["Giuseppe Caliendo"]
__license__ = "MIT"
__version__ = "0.0.1"
__maintainer__ = "Giuseppe Caliendo"
__status__ = "Development"

def main():
    try:
        print("BEGIN")
        
        print("Connecting to Arduino...")
        serialCom = serial.Serial('COM3', 9600)
        print("Connected.")


        print("Retrieving new quiz...")
        params = (('amount', '1'),('category', '18'), ('difficulty', 'easy'), ('type', 'boolean'))
        response = requests.get('https://opentdb.com/api.php', params=params)
        questions = json.loads(response.text)
        
        if questions["response_code"] == 0:
            print("Retrieved.")
            questionList = questions["results"]

            print("Generating data for Arduino...")
            counter = 1
            correct = 0
            for question in questionList:
                question_display = question["question"]
                correct_answer = question["correct_answer"].upper() 
                print(question_display)
                answer = input().upper()
                if answer == correct_answer:
                    print("WOW!")
                    correct = correct + 1
                else:
                    print("Nooo! The correct answer was " + correct_answer)
                counter = counter + 1
        else:
            print("Error retrieving questions set from opentdb API")
        
        print("END")

    finally:
        print("Quitting script")
        quitSignal = "-1" + '\n'
        serialCom.write(quitSignal.encode())

if __name__ == '__main__':
    main()