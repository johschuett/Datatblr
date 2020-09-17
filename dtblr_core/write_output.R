# print_output.R
# This script writes the LaTeX code chunks for every generated table in the
# original order of the meta.CSV file in a .tex file

preamble <- paste("\\documentclass[10pt, twoside]{article}

\\usepackage[T1]{fontenc}
\\usepackage[utf8]{inputenc}
\\usepackage[ngerman]{babel}
\\usepackage{amssymb}
\\usepackage{array}
\\usepackage{booktabs}
\\usepackage{dcolumn}
\\usepackage[left = .5in, right = .5in, top = 1in, bottom = 1in]{geometry}
\\usepackage{ltxtable}
\\usepackage{multirow}
\\usepackage{tabularx}

\\newcommand{\\mc}[1]{\\multicolumn{1}{c}{#1}}
\\newcolumntype{.}[1]{D{.}{.}{#1}}

\\begin{document}

\\title{", survey_title, "}
\\date{}

\\maketitle", sep = "")

write(preamble, file = "report.tex", append = FALSE)

for (.el in var_name) {
  variable_positions <- dplyr::filter(order, (order[, 1] == .el))
  variable_positions <- as.numeric(variable_positions[1, 2])
  write(output[[variable_positions]], file = "report.tex", append = TRUE)
}

write("\\end{document}", file = "report.tex", append = TRUE)

system("pdflatex report.tex")
system("rm *.aux *log")

# Free memory
rm(.el, variable_positions)
