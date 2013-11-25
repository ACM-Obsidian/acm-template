 #-*- encoding: utf-8 -*-

import os

remark="remark.md"
main = ""

def dfs(level, path):
    global main
    for i in os.listdir(path):
        j = i
        i = path + '/' + i
        if (os.path.isdir(i) and i != "./.git"):
            main += "\\%ssection{%s}"%(level, j) + "\n"
            dfs(level + "sub", i)
        else:
            if (j == remark): main += "\\input{%s}\n"%(i)
            else: 
                if (level != ""): main += "\\code{%s}\\newpage"%(i) + "\n"

dfs("", ".")

print r"""

\documentclass[a4paper,11pt]{article}

\usepackage{amsmath}
\usepackage{amssymb}
\usepackage{cmap}
\usepackage{geometry}
\usepackage[bookmarks=true,colorlinks,linkcolor=black]{hyperref}
\usepackage{indentfirst}
\usepackage{xeCJK}
\usepackage{titlesec}

\usepackage{listings} %插入代码
\usepackage{xcolor} %代码高亮
 
\definecolor{mygreen}{rgb}{0,0.6,0}
\definecolor{AnswerColor}{rgb}{0.8,0,0}
\lstset{
%	xleftmargin=0.5em, xrightmargin=0.5em,aboveskip=1em,
	tabsize=4,
	basicstyle=\ttfamily\small, 
	frame=none,
	breaklines,
	extendedchars=false
	keywordstyle=\bfseries\color{blue}, 
	commentstyle=\itshape\color{mygreen}, 
}

\newcommand{\code}[1]{\lstinputlisting{#1}}

\geometry{margin=1in}

\setCJKmainfont[BoldFont={Adobe Heiti Std}]{Adobe Song Std}
\setCJKfamilyfont{hei}{Adobe Heiti Std}
\setmainfont{Times New Roman}

\title{Obsidian 模板}
\author{北京大学}
\date{\today}

\begin{document}
\maketitle
\tableofcontents
\newpage
""" + main + """
\end{document}
"""

