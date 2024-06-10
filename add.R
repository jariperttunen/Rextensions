
add1 <- function(a) {
    cat("R received vector from C: ", a, "\n")
    cat("Is double",is.double(a),"\n")
    cat("Is vector",is.vector(a),"\n")
    cat("Is matrix",is.matrix(a),"\n")
    cat("Dimensions",dim(a),"\n")
    cat("Length",length(a),"\n")
    a = a + 1.0;
    cat("After addition",a,"\n")
    return(a)
}

addm <- function(m){
    cat("R received data from C:",m,"\n")
    cat("Is double",is.double(m),"\n")
    cat("Is matrix",is.matrix(m),"\n")
    cat("Is vector",is.vector(m),"\n")
    cat("Matrix dimensions",dim(m),"\n")
    x = dim(m)[1]
    y = dim(m)[2]
    for (i in 1:x){
        for (j in 1:y){
            cat(m[i,j]," ")
        }
        cat("\n")
    }
    m = m+2
    cat("After addition\n")
    for (i in 1:x){
        for (j in 1:y){
            cat(m[i,j]," ")
        }
        cat("\n")
    }
    return (m)
}
