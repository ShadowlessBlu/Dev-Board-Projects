import speech_recognition
import pyttsx3
import openai

recognizer = speech_recognition.Recognizer()
voice_engine = pyttsx3.init()

openai.api_key = "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"

def chatgpt(text):
    response = openai.ChatCompletion.create(
        model="gpt-3.5-turbo",
        temperature=0.8,
        max_token=1000,
        message=[
            {"role": "system", "content": "tou are a personal assistant."},
            {"role": "user", "content": text}
        ]
    )

    return response.choices[0].message.content

def louder():
    try:
        with speech_recognition.Microphone() as source:
            voice = recognizer.listen(source, phrase_time_limit=6)
            print("listen")
            transcribe_voice = recognizer.recognize_google(voice)
            transcribe_voice = transcribe_voice.lower()
            print(f"I heard {transcribe_voice}")
    except Exception as e:
        print(f"[ERROR] {e}")

    print("I am speaking louder...")

def text_to_voice(text):
    voice_engine.say(text)
    voice_engine.runAndWait()


while True:
    text_to_voice("I want gob333")
    chatgpt("HELLO")
   # louder()
