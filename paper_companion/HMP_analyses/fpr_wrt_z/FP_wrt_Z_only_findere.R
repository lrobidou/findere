
jpeg(file="fpr_simple.png",width=11,height=8)
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

plot(data$findere_FPR*100~data$z,xlab="k-s",ylab="FP rate (%)", lwd=2, pch=15, col="blue", 
     bg = "blue", lty=2, type="o",   cex=2, ylim=c(0,6), xlim=c(0,10), main="False positive rate, k=31", cex.main = 2, cex.lab = 2, cex.axis = 2)


par(new = TRUE)






legend( x="right", 
        legend=c(""), 
        col=c("blue"), lty=c(2,1),
        pch=c(15,19), lwd=2,merge=TRUE, bty = "n", cex=c(2,2) )






dev.off()




