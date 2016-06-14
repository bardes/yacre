# Yet Another Crappy Render Engine (YACRE) - Manual
YACRE é uma *render engine* do tipo *ray tracing*, desenvolvida com o objetivo
de aprender e experimentar com os conceitos de iluminação, sombreamento e
modelagem 3D.

---

## Características
  - Iluminação direta e indireta
  - Sombreamento (*hard shadows*)
  - Materiais difusos e reflexivos
  - Antialiasing via superamostragem

## Compilação
YACRE depende apenas de duas bibliotecas externas:
[SFML](http://www.sfml-dev.org/) e [glm](http://glm.g-truc.net/). Ambas podem
ser facilmente obtidas através do seu gerenciador de pacotes favorito. Tendo as
dependências satisfeitas basta clonar o repositório: `git clone
git://github.com/bardes/yacre.git`.

Na raiz do repositório há um *Makefile*, basta usar o comando `make` (ou `make
-j $(nproc)` caso esteja com pressa) para compilar o projeto. Após a compilação
um executável chamado `yacre` deve estar disponível na raiz.

## Uso
```
./yacre <largura> <altura> [saida.formato]
```

O programa pode receber até três argumentos, sendo dois deles obrigatórios e um
opcional. Os argumentos são:

  - **largura**: Largura da imagem renderizada em pixels.
  - **altura**: Altura da imagem renderizada em pixels.
  - **saida.formato**: Quando definido este argumento salva a imagem
    renderizada com o nome dado. O formato da imagem é determinado através da
    extensão.
