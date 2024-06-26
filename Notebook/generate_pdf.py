import subprocess
import os
import shutil

code_dir = "../"
title = "AC2++"


def get_sections():
    sections = []
    section_name = None
    with open("contents.txt", "r") as f:
        for line in f:
            if "#" in line:
                line = line[: line.find("#")]
            line = line.strip()
            if len(line) == 0:
                continue
            if line[0] == "[":
                section_name = line[1:-1]
                subsections = []
                if section_name is not None:
                    sections.append((section_name, subsections))
            else:
                tmp = line.split("\t", 1)
                if len(tmp) == 1:
                    raise ValueError("Subsection parse error: %s" % line)
                filename = tmp[0]
                subsection_name = tmp[1]
                if subsection_name is None:
                    raise ValueError("Subsection given without section")
                subsections.append((filename, subsection_name))
    return sections


def get_style(filename):
    ext = filename.lower().split(".")[-1]
    if ext in ["c", "cc", "cpp"]:
        return "cpp"
    elif ext in ["java"]:
        return "java"
    elif ext in ["py"]:
        return "py"
    else:
        return "txt"


# TODO: check if this is everything we need


def texify(s):
    # s = s.replace('\'', '\\\'')
    # s = s.replace('\"', '\\\"')
    return s


def formatear_codigo(sections):
    for section_name, subsections in sections:
        for filename, subsection_name in subsections:
            archivo_entrada = code_dir + filename
            lenguaje = get_style(archivo_entrada)
            carpeta = code_dir + "format/"
            archivo_salida = carpeta + filename.split("/")[-1]
            if not os.path.exists(carpeta):
                os.makedirs(carpeta)

            if lenguaje == "cpp":
                comando = f"clang-format -style=file:my_clang_format.txt -assume-filename={archivo_entrada} {archivo_entrada}"
                print(comando)
                salida_formateada = subprocess.check_output(
                    comando, shell=True, universal_newlines=True
                )
                salida_formateada = salida_formateada.replace("Tiempo:", "\n * Tiempo:")
                salida_formateada = salida_formateada.replace("Uso:", "\n * Uso:")
                salida_formateada = salida_formateada.replace(
                    "Complejidad:", "\n * Complejidad:"
                )
                with open(archivo_salida, "w") as f:
                    f.write(salida_formateada)
            else:
                shutil.copyfile(archivo_entrada, archivo_salida)


def get_tex(sections):
    tex = ""
    for section_name, subsections in sections:
        tex += "\\section{%s}\n" % texify(section_name)
        for filename, subsection_name in subsections:
            tex += "\\subsection{%s}\n" % texify(subsection_name)
            tex += "\\raggedbottom\\lstinputlisting[style=%s]{%s/format/%s}\n" % (
                get_style(filename),
                code_dir,
                filename.split("/")[-1],
            )
            tex += "\\hrulefill\n"
        tex += "\\newpage\n"
        tex += "\n"
    return tex


if __name__ == "__main__":
    sections = get_sections()
    formatear_codigo(sections)
    tex = get_tex(sections)
    with open("contents.tex", "w") as f:
        f.write(tex)
    latexmk_options = ["latexmk", "-pdf", "notebook.tex"]
    subprocess.call(latexmk_options)
    remove_files = [
        "notebook.fls",
        "notebook.aux",
        "notebook.fdb_latexmk",
        "notebook.log",
        "notebook.out",
        "notebook.toc",
    ]
    for file in remove_files:
        if os.path.exists(file):
            os.remove(file)

    if os.path.exists(code_dir + "format"):
        shutil.rmtree(code_dir + "format")
