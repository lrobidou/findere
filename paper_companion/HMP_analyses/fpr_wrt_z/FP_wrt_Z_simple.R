
jpeg(file="fpr_simple.jpg",width=11,height=8)
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
par(mar=c(5,5,5,1))
data = read.table("data_FP_K31_hmp.txt", head=T)

plot(data$AMQ_FPR*100~data$z,xlab="z value",ylab="FP rate (%)", lwd=2, pch=15, col="blue", 
     bg = "blue", lty=2, type="o",   cex=2, ylim=c(0,7), xlim=c(0,10), main="False positive rate, K=31", cex.main = 2, cex.lab = 2, cex.axis = 2)


par(new = TRUE)
plot(data$findere_FPR*100~data$z,type="o",axes=FALSE,xlab="",ylab="",pch=19, col="red", ylim=c(0,7), xlim=c(0,5), cex=2)





legend( x="topleft", 
        legend=c("Bloom Filter (5%)","findere"), 
        col=c("blue","red"), lty=c(2,1),
        pch=c(15,19), lwd=2,merge=TRUE, bty = "n", cex=c(2,2) )






dev.off()




