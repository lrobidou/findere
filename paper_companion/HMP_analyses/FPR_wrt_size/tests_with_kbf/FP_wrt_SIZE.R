
pdf(file="fpr_size.pdf",width=6,height=4)
resetPar <- function() {
  dev.new()
  op <- par(no.readonly = TRUE)
  dev.off()
  op
}
resetPar()


dev.new()


setwd("~/workspace/findere/paper_companion/HMP_analyses/FPR_wrt_size/tests_with_kbf")
dev.off()
#par(mar=c(5,5,3,6), cex.axis=2, cex.lab=2, cex.main = 2)
# par(mar=c(5,5,3,6))
data = read.table("data_FP_wrt_size.txt", head=T)
data$sizeGiga = data$size/8000000000


dataKbf = read.table("data_FP_kbf_wrt_size.txt", head=T)



plot(data$FPR_findere~data$sizeGiga,xlab="Bloom Filter size (Go)",ylab="FP rate (%) - log scale", pch=15, col="red",log="y",yaxt="n",
     bg = "red", type="l",  cex=2, main="False positive rate, depending on the Bloom filter size, K=31", cex.main = 1, cex.lab = 1, cex.axis = 1,
     xlim=c(0,0.6))
points(data$FPR_BF~data$sizeGiga,type="l",axes=FALSE,xlab="",ylab="",pch=19, lty=2, col="blue",  cex=1, log="y")
points(dataKbf$FPR_KBF1~dataKbf$size,type="o",axes=FALSE,xlab="",ylab="",pch=19, lty=2, col="orange",  cex=1, log="y")
points(dataKbf$FPR_KBF2~dataKbf$size,type="o",axes=FALSE,xlab="",ylab="",pch=21, lty=2, col="orange",  cex=1, log="y")

yticks<-c(0.1,0.5,1,5,10, 50)
axis(2,at=yticks,labels=yticks)

par(new = TRUE)#, mar=c(5,5,3,6))


legend( x="top", 
        legend=c("Bloom filter","findere", "1-kBF", "2-kBF"), 
        col=c("blue","red", "orange", "orange"), lty=c(2,1,2,2),
        lwd=1, merge=TRUE, bty = "n",   pch=c(19,15,19,21))


dev.off()



