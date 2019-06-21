
CREATE VIEW [dbo].[ViewSpotInfo]
AS
SELECT dbo.Spots.ID, dbo.Spots.Name, 
    dbo.Customers.Name AS CustomerName, 
    dbo.Agency.Name AS AgencyName, 
    dbo.TypeOfBusiness.Name AS Business, 
    dbo.Voices.Name AS Voice, dbo.HD.Path, dbo.Spots.FileName, 
    dbo.Spots.Obs, 
    dbo.Spots.Finish - dbo.Spots.Start AS Length
FROM dbo.Spots INNER JOIN
    dbo.Customers ON 
    dbo.Spots.CustomerID = dbo.Customers.ID LEFT OUTER JOIN
    dbo.HD ON dbo.Spots.PathID = dbo.HD.ID LEFT OUTER JOIN
    dbo.Voices ON 
    dbo.Spots.MainVoiceID = dbo.Voices.ID LEFT OUTER JOIN
    dbo.TypeOfBusiness ON 
    dbo.Spots.TypeOfBusinessID = dbo.TypeOfBusiness.ID LEFT OUTER
     JOIN
    dbo.Agency ON dbo.Spots.AgencyID = dbo.Agency.ID



