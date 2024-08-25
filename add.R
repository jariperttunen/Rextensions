
add1 <- function(v) {
    cat("2. In R program","\n")
    cat("R received vector from C: ", v, "\n")
    cat("Is double",is.double(v),"\n")
    cat("Is vector",is.vector(v),"\n")
    cat("Is matrix",is.matrix(v),"\n")
    cat("Dimensions",dim(v),"\n")
    cat("Length",length(v),"\n")
    v = v + 1.0;
    cat("Vector after addition v=v+1:",v,"\n\n")
    return(v)
}

addm <- function(m){
    cat("2. In R program","\n")
    cat("R received matrix from C\n")
    cat("Matrix in contiguous memory:",m,"\n")
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
    cat("Matrix after addition m=m+2:\n")
    for (i in 1:x){
        for (j in 1:y){
            cat(m[i,j]," ")
        }
        cat("\n")
    }
    cat("\n")
    return (m)
}

mrowfirst<-function(m){
    cat("2. In R program","\n")
    cat("R received matrix from C\n")
    cat("Matrix in contiguous memory:",m,"\n")
    cat("Is double",is.double(m),"\n")
    cat("Is matrix",is.matrix(m),"\n")
    cat("Is vector",is.vector(m),"\n")
    cat("Matrix dimensions",dim(m),"\n")
    cat("Indexing matrix","\n")
    x = dim(m)[1]
    y = dim(m)[2]
    for (i in 1:x){
        for (j in 1:y){
            cat(m[i,j]," ")
        }
        cat("\n")
    }
    cat("Create new matrix filled by rows","\n")
    m1<-matrix(m,nrow=x,ncol=y,byrow=TRUE)
    for (i in 1:x){
        for (j in 1:y){
            cat(m1[i,j]," ")
        }
        cat("\n")
    }
    cat("The new matrix in contiguous memory:",m1,"\n")
    
}

matrix3d <- function(v){
    cat("2. In R program","\n")
    cat("Received vector for 3D matrix","\n")
    cat("Vector in contiguos memory",v,"\n")
    cat("Creating 3D matrix from the vector\n")
    m3d <- array(v, c(3,5,6));
    for (i in 1:3){
        for (j in 1:5){
            for (k in 1:6){
                cat(m3d[i,j,k]," ")
            }
            cat("\n")
        }
        cat("\n")
    }
    m3d = m3d + 2
    cat("3D matrix after addition m3d=m3d+2","\n")
    for (i in 1:3){
        for (j in 1:5){
            for (k in 1:6){
                cat(m3d[i,j,k]," ")
            }
            cat("\n")
        }
        cat("\n")
    }
    return (m3d)
}
