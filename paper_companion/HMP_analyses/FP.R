
pdf(file="fpr.pdf",width=11,height=8)
resetPar <- function() {
  dev.new()
  op <- par(no.readonly = TRUE)
  dev.off()
  op
}
resetPar()


dev.new()
dev.off()
par(mar=c(5,5,3,6), cex.axis=2, cex.lab=2, cex.main = 2)
#par(mar=c(5,5,5,1))
data = read.table("data_FP_K31_hmp.txt", head=T)
datime = read.table("data_time_K31_hmp.txt", head=T)
data$FP_BFk = data$findere_FPR-data$construction_FPR
plot(data$AMQ_FPR*100~data$z,xlab="z value",ylab="FP rate (%)", lwd=2, pch=15, col="blue", 
     bg = "blue", lty=2, type="o",  mgp=c(3,1,0), cex=2, ylim=c(0,7), xlim=c(0,10), main="False positive rate, depending on z, K=31", cex.main = 2, cex.lab = 2, cex.axis = 2)


par(new = TRUE, mgp=c(3,1,0))
plot(data$findere_FPR*100~data$z,type="o",axes=FALSE,xlab="",ylab="",pch=19, col="red", ylim=c(0,7), xlim=c(0,5), cex=2)



par(new = TRUE, mgp=c(3,1,0))
plot(data$construction_FPR*100~data$z,type="o",axes=FALSE,xlab="",ylab="",pch=21, col="orange", ylim=c(0,7), xlim=c(0,5), cex=2)


legend( x="topleft", 
        legend=c("Bloom Filter (5%)","findere", "findere construction FP"), 
        col=c("blue","red", "orange"), lty=c(2,1,1),
        pch=c(15,19, 21), lwd=2,merge=TRUE, bty = "n", cex=c(2,2,2) )





# INCRUSTATION
par(new=TRUE, oma =c(5.6,24.6,12.2,3), cex.axis=1, cex.lab=1)
layout(matrix(1:1,1))



#plot(rnorm(100), runif(100), col="blue", xlab="", ylab="")
plot(data$AMQ_FPR*100~data$z,xlab="",ylab="",lwd=1, pch=15, cex=1, col="blue", type="o", lty=2,mgp=c(2,0.5,0), ylim=c(0,100), xlim=c(0,29))

par(new = TRUE, mgp=c(3,1,0))
plot(data$findere_FPR*100~data$z,type="o",axes=FALSE,xlab="",ylab="",cex=1,pch=19, col="red", ylim=c(0,100), xlim=c(0,29))



par(new = TRUE, mgp=c(3,1,0))
plot(data$construction_FPR*100~data$z,type="o",axes=FALSE,xlab="",ylab="",cex=1,pch=21, col="orange", ylim=c(0,100), xlim=c(0,29))

# par(new = TRUE, mgp=c(3,1,0))
# plot(datime$findere/1000~datime$z,type="b",axes=FALSE,xlab="",ylab="",pch=1, cex=1, col="black", xlim=c(0,29), ylim=c(0,60))
# axis(4, ylim=c(0,60), las=1, cex.lab=2, mgp=c(3,1,0))

dev.off()




