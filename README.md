### HHC OPD - Patient Registration Portal

![HHC Logo](https://i.ibb.co/ZfyDKDj/HHC-Logo.png)

Hospital Registration Portal is, a FOSS under Apache 2 License, developed specifically for Hathidah Health Care, which is an integrated unit of health care having objective of taking care of Physical, Mental and Social Health of Society through Allopathy, Homeopathy, Ayurveda, Yoga facilities both online and offline.

> Hathidah Health Care is the brainchild of Sri Prakash (my father) and Dr. Satya Prakash (my uncle) - A Renowned Cardiologist in Indian State of Bihar, which took birth during the unprecedented global crisis of COVID-19, experiencing the hardship in Health Sector on ground.
>
> It has been started as a source of engagement for him post retirement and also as a way to carry on will of his late father, a Freedom Figher, Social Worker and an ex-MLA, to serve the society and motherland in any way possible.

Taking into consideration the nature of the entity to serve the people, this project has been made open-source with the hope that it may be useful for people in one way or the other.

## Disclaimer
```
The project is under active development (even if there may be no recent commits on the repo), hence might change drastically or the main branch might have a program breaking bug at any point of time.
```

> TODO List: [Find Here!](TODO.md)

## Screenshots

> Add Patient View

![Add Patient View](https://i.ibb.co/g3FPcdg/Add-Patient-Window.png)

> Search Patient View

![Search Patient View](https://i.ibb.co/mB40QKZ/Search-Patient-Window.png)

> Add Visit View

![Add Visit View](https://i.ibb.co/DLvRvBH/Add-Visit.png)

> Show All Visit View

![Show All Visit View](https://i.ibb.co/Ttx7XGK/View-All-Visits.png)

> Final Generated Receipt (Printable)

![Generated Receipt](https://i.ibb.co/8Pb2cvL/Generated-Receipt.png)

## How to Configure?

Make sure the Deployment folder has a config.ini else the program wont start

> Template for config.ini

```
[db_settings]
type=QPSQL
host=localhost
username=postgres
password=
db=hhc_main

[paths]
csv_export="Path to CSV Exports"
pdf_export="Path to PDF Exports"
```

> How to change Logos and Icons will be updated soon!
>
> How to load CSV for easy viewing in Excel will be updated soon!

## How to Use?
1. Downloading the Binary
	* Find the latest release binary in Releases
	> Warning: This Release will be specific to Hathidah Health Care (HHC), an entity owned by Sri Prakash.
	>
	> Download this only if you want to get a hang of what is the application and how it handles situations specific to your needs.

2. Building from Source
	* Clone the Repo
	* Open the ```HHC_OPD.pro``` file in QtCreator with min Qt version as mentioned below.
	* Make sure ```qmake``` is set as the Build tool for the project
	* Compile in Debug/Release Mode as required.

## Tools

* Qt Toolkit 6.2.0 -> [LICENSE - LGPL](https://doc.qt.io/qt-5/lgpl.html)
* PostgreSQL 13 -> [LICENSE - PostgreSQL](https://www.postgresql.org/about/licence/)


## License

> Developed by Kushagra (2021)
>
> Under [Apache 2.0 License](https://raw.githubusercontent.com/kushagra10025/Hospital-Registration-Portal/main/LICENSE)
