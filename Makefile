main.pdf: main.tex
	xelatex main.tex
	xelatex main.tex #get content

main.tex: parse.py
	python2 parse.py > main.tex

.PHONY: clean
clean:
	rm main.out main.aux main.log main.toc main.tex main.pdf -f
