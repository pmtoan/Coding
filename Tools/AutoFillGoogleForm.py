import requests
from random import randint


def random_submit():
	advice = [
		'Cần vệ sinh môi trường xung quanh sạch sẽ',
		'Cần cải tiến các màn biểu diễn',
		'Cần mở rộng hơn'
	]
	data = []
	q1 = randint(0,1)
	if q1 == 0:
		data.append('Không')
		q6 = randint(0,1)
		if q6 == 0:
			data.append('Không')
		else:
			data.append('Có')
		q7 = randint(0,1)
		if q7 == 0:
			data.append('Không')
		else:
			data.append('Có')
		form_data = {
			'entry.381086474': data[0],
			'entry.32371606': data[1],
			'entry.348238149': data[2],
			'facebook'
			'bank'
		    ''
		}

	else:
		data.append('Có')
		q2 = randint(0,1)
		if q2 == 0:
			data.append('Không')
		else:
			data.append('Có')
		q3 = randint(1,5)
		q3 = str(q3)
		data.append(q3)
		q4 = randint(0,2)
		data.append(advice[q4])
		q5 = randint(0,1)
		if q5 == 0:
			data.append('Không')
		else:
			data.append('Có')
		form_data = {
			'entry.381086474': data[0],
			'entry.611803027': data[1],
			'entry.1039090056':data[2],
			'entry.348904928':data[3],
			'entry.491772700':data[4]
		}
	return form_data


def fill():
	url = 'https://docs.google.com/forms/d/14fqWebz9EEbW-fg0uMPUghQu08nmo0jn1Adpl5H6Qy8/formResponse'
	form_data = random_submit()
	user_agent = {'Referer':'https://docs.google.com/forms/d/14fqWebz9EEbW-fg0uMPUghQu08nmo0jn1Adpl5H6Qy8/formResponse','User-Agent': "Mozilla/5.0 (X11; Linux i686) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/28.0.1500.52 Safari/537.36"}
	r = requests.post(url, data=form_data, headers=user_agent)
	
	print(r)

if __name__ == "__main__":
	for i in range(1,20):
		fill()