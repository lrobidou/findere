
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
plot(data$FPR_BF~data$sizeGiga,xlab="Bloom Filter size (MB)",ylab="FP rate (%) - log scale", pch=15, col="blue", log="y",
     bg = "blue", type="l",  lty=2, mgp=c(3,1,0), cex=2, main="False positive rate, depending on the Bloom filter size, K=31", cex.main = 1, cex.lab = 1, cex.axis = 1)



par(new = TRUE)
segments(-1000, 0.1, 20, 0.1,
         col = par("fg"), lty = 3, lwd = par("lwd"), cex=2)

segments(0.4, 0.000001,  0.4, 0.2,
         col = par("fg"), lty = 3, lwd = par("lwd"), cex=2)
segments(17, 0.000001, 17, 0.2,
         col = par("fg"), lty = 3, lwd = par("lwd"), cex=2)



# segments(-1000, 1, 5, 1,
#          col = par("fg"), lty = 3, lwd = par("lwd"), cex=2)
# segments(2.4, 0.000001, 2.4, 6,
#          col = par("fg"), lty = 3, lwd = par("lwd"), cex=2)
# segments( 0.05, 0.000001,  0.05, 6,
#          col = par("fg"), lty = 3, lwd = par("lwd"), cex=2)

par(new = TRUE, mgp=c(3,1,0))
plot(data$FPR_findere~data$sizeGiga,type="l",axes=FALSE,xlab="",ylab="",pch=19, col="red",  cex=2, log="y")


legend( x="top", 
        legend=c("Bloom Filter","findere"), 
        col=c("blue","red"), lty=c(2,1),
        lwd=2, merge=TRUE, bty = "n", cex=c(1,1) )


dev.off()



