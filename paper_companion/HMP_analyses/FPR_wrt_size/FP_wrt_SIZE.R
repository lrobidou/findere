
pdf(file="fpr_size.pdf",width=6,height=4)
resetPar <- function() {
  dev.new()
  op <- par(no.readonly = TRUE)
  dev.off()
  op
}
resetPar()


dev.new()



dev.off()
#par(mar=c(5,5,3,6), cex.axis=2, cex.lab=2, cex.main = 2)
data = read.table("data_FP_wrt_size.txt", head=T)
data$sizeGiga = data$size/8000000000
plot(data$FPR_BF~data$sizeGiga,xlab="Bloom Filter size (GB)",ylab="FP rate (%) - log scale", pch=15, col="blue",log="y",yaxt="n",xaxt="n",
     bg = "blue", type="l",  lty=2,  cex=2, main="False positive rate, depending on the Bloom filter size, K=31", cex.main = 1, cex.lab = 1, cex.axis = 1)
yticks<-c(0.1,0.5,1,5,10, 50)
axis(2,at=yticks,labels=yticks)
xticks<-c(0,0.16,5,10,15,17, 20,25,30)
axis(1,at=xticks,labels=xticks)

6644980503/8000000000
1053472602/8000000000


segments(-1000, 0.1, 20, 0.1,
         col = par("fg"), lty = 3, lwd = par("lwd"), cex=2)


segments(0.16, 0.000001,  0.16, 0.2,
         col = par("fg"), lty = 3, lwd = par("lwd"), cex=2)

segments(17, 0.000001, 17, 0.2,
         col = par("fg"), lty = 3, lwd = par("lwd"), cex=2)

par(new = TRUE)#, mgp=c(3,1,0))
plot(data$FPR_findere~data$sizeGiga,type="l",axes=FALSE,xlab="",ylab="",pch=19, col="red",  cex=1, log="y")

legend( x="top", 
        legend=c("Bloom filter","findere"), 
        col=c("blue","red"), lty=c(2,1),
        lwd=1, merge=TRUE, bty = "n", cex=c(1,1) )


dev.off()



